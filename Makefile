CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
GDB?=gdb-multiarch
MACH=cortex-m4
LIB =-I ./cmsis/CMSIS/Device/ST/STM32L4xx/Include/ -I ./cmsis/CMSIS/Include/
CFLAGS=-Wall -g -O1 -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16  $(LIB) 
LDFLAGS=-g -nostdlib -T linker.lds -Wl,-Map=final.map -ffreestanding 
ASFLAGS =-g -mcpu=cortex-m4 -mthumb 
OBJS=bootloader.o startup_file.o main.o pripherique_config.o button_configuration.o
EXE=test.elf
#all: main.o startup_file.o 

$(EXE):$(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly
debug: $(EXE)
	$(GDB) $<
clean:
	rm -f *.o *.elf
.PHONY:
	clean debug connect
