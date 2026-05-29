#!/usr/bin/env python3
import argparse
import re
from pathlib import Path

from PIL import Image, ImageOps


def rgb565(r, g, b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


def center_crop_square(image):
    width, height = image.size
    side = min(width, height)
    left = (width - side) // 2
    top = (height - side) // 2
    return image.crop((left, top, left + side, top + side))


def format_array(symbol, values, width, height):
    lines = [
        f"const uint16_t {symbol}[{height}][{width}] = {{",
    ]
    for y in range(height):
        row = ",".join(f"0x{values[y * width + x]:04X}" for x in range(width))
        lines.append("{" + row + "},")
    lines[-1] = lines[-1].rstrip(",")
    lines.append("};")
    return "\n".join(lines)


def replace_array(source, symbol, replacement):
    pattern = re.compile(
        r"const\s+uint16_t\s+"
        + re.escape(symbol)
        + r"\s*\[\s*240\s*\]\s*\[\s*240\s*\]\s*=\s*\{.*?\n\};",
        re.DOTALL,
    )
    new_source, count = pattern.subn(replacement, source, count=1)
    if count != 1:
        raise SystemExit(f"Tableau {symbol}[240][240] introuvable dans le fichier cible.")
    return new_source


def main():
    parser = argparse.ArgumentParser(
        description="Convertit une image en tableau C RGB565 240x240 pour ST7789."
    )
    parser.add_argument("input", type=Path, help="Image source PNG/JPG.")
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=Path("image_240x240.c"),
        help="Fichier C de sortie si --replace n'est pas utilise.",
    )
    parser.add_argument(
        "--replace",
        type=Path,
        help="Remplace le tableau existant dans ce fichier, par exemple ST7789-STM32-master/ST7789/fonts.c.",
    )
    parser.add_argument("--symbol", default="image_240x240", help="Nom du tableau C.")
    parser.add_argument(
        "--byteswap",
        action="store_true",
        help="Inverse les octets dans chaque uint16_t pour les drivers qui envoient la RAM little-endian directement.",
    )
    args = parser.parse_args()

    image = Image.open(args.input)
    image = ImageOps.exif_transpose(image).convert("RGB")
    image = center_crop_square(image)
    image = image.resize((240, 240), Image.Resampling.LANCZOS)

    values = []
    for r, g, b in image.getdata():
        value = rgb565(r, g, b)
        if args.byteswap:
            value = ((value & 0xFF) << 8) | (value >> 8)
        values.append(value)

    array_text = format_array(args.symbol, values, 240, 240)

    if args.replace:
        source = args.replace.read_text()
        args.replace.write_text(replace_array(source, args.symbol, array_text))
    else:
        args.output.write_text('#include "fonts.h"\n\n' + array_text + "\n")


if __name__ == "__main__":
    main()
