CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
GDB    ?= gdb-multiarch

EXE     = test.elf
MAP     = final.map

CPU_FLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

INC_DIRS = \
	cmsis/CMSIS/Device/ST/STM32L4xx/Include \
	cmsis/CMSIS/Include \
	drivers \
	firmware \
	ST7789-STM32-master/ST7789

CPPFLAGS = -DSTM32L475xx $(addprefix -I,$(INC_DIRS))
CFLAGS   = -Wall -g3 -Og -ffreestanding $(CPU_FLAGS)
ASFLAGS  = -g $(CPU_FLAGS)
LDFLAGS  = -g -nostdlib -T linker.lds -Wl,-Map=$(MAP) -ffreestanding $(CPU_FLAGS)

C_SOURCES = \
	startup_file.c \
	main.c \
	drivers/gpio.c \
	drivers/Timer.c \
	drivers/dma.c \
	drivers/spi.c \
	ST7789-STM32-master/ST7789/st7789.c \
	ST7789-STM32-master/ST7789/fonts.c \
	firmware/led_service.c \
	firmware/timer_service.c \
	Application.c \
	tools/StartImage.c

ASM_SOURCES = \
	bootloader.s

OBJS = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.s=.o)
EXTRA_CLEAN = firmware/timer_service

.PHONY: all clean debug connect

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug: $(EXE)
	$(GDB) $<

clean:
	rm -f $(OBJS) $(EXE) $(MAP) $(EXTRA_CLEAN)
