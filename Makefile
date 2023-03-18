cc=arm-none-eabi-gcc
GDB?=gdb-multiarch
MACH=cortex-m4
LIB =-I /home/gweth/projet_usb/cmsis/CMSIS/Device/ST/STM32L4xx/Include/ -I /home/gweth/projet_usb/cmsis/CMSIS/Include/
CFLAG= -Wall -c -g -mcpu=$(MACH) -mthumb  -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -o0 $(LIB) 
LDFLAGS=-g -nostdlib -T linker.lds -Wl,-Map=final.map -ffreestanding 
OBJS=startup_file.o  main.o pripherique_config.o
EXE=test.elf
#all: main.o startup_file.o 

$(EXE):$(OBJS)
	$(cc) $(LDFLAGS) $^ -o $@
%.o: %.c
	$(cc) $(CFLAG) $^ -o $@
connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly
debug: $(EXE)
	$(GDB) $<
clean:
	rm -f *.o *.elf
.PHONY:
	clean
