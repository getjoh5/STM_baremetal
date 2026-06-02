#!/usr/bin/env python3
import argparse
import re
from datetime import datetime
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont, ImageOps


WIDTH = 240
HEIGHT = 240


def rgb565(r, g, b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


def parse_color(value):
    value = value.strip()
    if re.fullmatch(r"#[0-9a-fA-F]{6}", value):
        return tuple(int(value[i : i + 2], 16) for i in (1, 3, 5))
    if re.fullmatch(r"0x[0-9a-fA-F]{4}", value):
        color = int(value, 16)
        r = ((color >> 11) & 0x1F) << 3
        g = ((color >> 5) & 0x3F) << 2
        b = (color & 0x1F) << 3
        return (r, g, b)
    raise argparse.ArgumentTypeError("Couleur attendue: #RRGGBB ou 0xRGB565")


def center_crop_square(image):
    width, height = image.size
    side = min(width, height)
    left = (width - side) // 2
    top = (height - side) // 2
    return image.crop((left, top, left + side, top + side))


def load_background(path):
    image = Image.open(path)
    image = ImageOps.exif_transpose(image).convert("RGB")
    image = center_crop_square(image)
    return image.resize((WIDTH, HEIGHT), Image.Resampling.LANCZOS).convert("RGBA")


def load_font(size, font_path=None):
    candidates = []
    if font_path:
        candidates.append(font_path)
    candidates.extend(
        [
            "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        ]
    )

    for candidate in candidates:
        try:
            return ImageFont.truetype(str(candidate), size)
        except OSError:
            pass
    return ImageFont.load_default()


def centered_text(draw, xy, text, font, fill, stroke_fill=None, stroke_width=0):
    x, y = xy
    bbox = draw.textbbox((0, 0), text, font=font, stroke_width=stroke_width)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    draw.text(
        (x - text_width // 2, y - text_height // 2),
        text,
        font=font,
        fill=fill,
        stroke_fill=stroke_fill,
        stroke_width=stroke_width,
    )


def draw_datetime_image(args):
    if args.background:
        canvas = load_background(args.background)
    else:
        canvas = Image.new("RGBA", (WIDTH, HEIGHT), args.bg_color + (255,))

    overlay = Image.new("RGBA", (WIDTH, HEIGHT), (0, 0, 0, 0))
    draw = ImageDraw.Draw(overlay)

    if args.panel:
        panel_color = args.panel_color + (args.panel_alpha,)
        draw.rounded_rectangle((16, 54, 224, 186), radius=12, fill=panel_color)

    now = args.datetime or datetime.now()
    date_text = now.strftime(args.date_format)
    time_text = now.strftime(args.time_format)

    date_font = load_font(args.date_size, args.font)
    time_font = load_font(args.time_size, args.font)
    label_font = load_font(args.label_size, args.font)

    if args.label and not args.time_only:
        centered_text(
            draw,
            (WIDTH // 2, 77),
            args.label,
            label_font,
            args.text_color + (255,),
            args.stroke_color + (255,),
            args.stroke_width,
        )

    if args.time_only:
        centered_text(
            draw,
            (WIDTH // 2, HEIGHT // 2),
            time_text,
            time_font,
            args.text_color + (255,),
            args.stroke_color + (255,),
            args.stroke_width,
        )
    else:
        centered_text(
            draw,
            (WIDTH // 2, 113),
            time_text,
            time_font,
            args.text_color + (255,),
            args.stroke_color + (255,),
            args.stroke_width,
        )
        centered_text(
            draw,
            (WIDTH // 2, 154),
            date_text,
            date_font,
            args.text_color + (255,),
            args.stroke_color + (255,),
            args.stroke_width,
        )

    return Image.alpha_composite(canvas, overlay).convert("RGB")


def format_array(symbol, values, width, height):
    lines = [f"const uint16_t {symbol}[{height}][{width}] = {{"]
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


def image_to_rgb565_values(image, byteswap=False):
    values = []
    for r, g, b in image.getdata():
        value = rgb565(r, g, b)
        if byteswap:
            value = ((value & 0xFF) << 8) | (value >> 8)
        values.append(value)
    return values


def parse_datetime(value):
    try:
        return datetime.strptime(value, "%Y-%m-%d %H:%M:%S")
    except ValueError as exc:
        raise argparse.ArgumentTypeError("Format attendu: 'YYYY-MM-DD HH:MM:SS'") from exc


def main():
    parser = argparse.ArgumentParser(
        description="Genere une image date/heure 240x240 en tableau C RGB565 pour ST7789."
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=Path("datetime_240x240.c"),
        help="Fichier C de sortie si --replace n'est pas utilise.",
    )
    parser.add_argument(
        "--replace",
        type=Path,
        help="Remplace le tableau existant dans ce fichier.",
    )
    parser.add_argument("--symbol", default="datetime_240x240", help="Nom du tableau C.")
    parser.add_argument(
        "--background",
        type=Path,
        help="Image de fond a recadrer en 240x240 avant d'ajouter la date/heure.",
    )
    parser.add_argument(
        "--preview",
        type=Path,
        help="Ecrit aussi une preview PNG de l'image generee.",
    )
    parser.add_argument(
        "--datetime",
        type=parse_datetime,
        help="Date/heure fixe pour tester, format: 'YYYY-MM-DD HH:MM:SS'.",
    )
    parser.add_argument("--date-format", default="%d/%m/%Y", help="Format strftime de la date.")
    parser.add_argument("--time-format", default="%H:%M", help="Format strftime de l'heure.")
    parser.add_argument(
        "--time-only",
        action="store_true",
        help="Dessine uniquement l'heure, centree sur fond noir ou sur --background.",
    )
    parser.add_argument("--label", default="STM32", help="Petit texte au-dessus de l'heure.")
    parser.add_argument("--font", type=Path, help="Chemin optionnel vers une police .ttf.")
    parser.add_argument("--label-size", type=int, default=17)
    parser.add_argument("--time-size", type=int, default=44)
    parser.add_argument("--date-size", type=int, default=24)
    parser.add_argument("--text-color", type=parse_color, default="#FFFFFF")
    parser.add_argument("--stroke-color", type=parse_color, default="#000000")
    parser.add_argument("--stroke-width", type=int, default=2)
    parser.add_argument("--bg-color", type=parse_color, default="#000000")
    parser.add_argument("--panel", action="store_true", help="Ajoute un panneau semi-transparent.")
    parser.add_argument("--panel-color", type=parse_color, default="#000000")
    parser.add_argument("--panel-alpha", type=int, default=130)
    parser.add_argument(
        "--byteswap",
        action="store_true",
        help="Inverse les octets pour un envoi direct little-endian via SPI.",
    )
    args = parser.parse_args()

    if not 0 <= args.panel_alpha <= 255:
        raise SystemExit("--panel-alpha doit etre entre 0 et 255.")

    image = draw_datetime_image(args)
    values = image_to_rgb565_values(image, args.byteswap)
    array_text = format_array(args.symbol, values, WIDTH, HEIGHT)

    if args.preview:
        image.save(args.preview)

    if args.replace:
        source = args.replace.read_text()
        args.replace.write_text(replace_array(source, args.symbol, array_text))
    else:
        args.output.write_text('#include "fonts.h"\n\n' + array_text + "\n")


if __name__ == "__main__":
    main()
