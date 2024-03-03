# Define the project name
PROJECT = fs-firmware-v4-c

# Define the microcontroller
MCU = atmega2560 

# Define the clock frequency
F_CPU = 16000000UL

# Define the programmer
PROGRAMMER = atmelice_isp

# Define the source files
SRC = $(wildcard *.c)

# Define the include files
INCLUDES = $(wildcard *.h)

# Define the compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Os

# Define the linker flags
LDFLAGS = -mmcu=$(MCU)

# Define the object files
OBJ = $(SRC:.c=.o)

# Define the hex file
HEX = $(PROJECT).hex

# Define the compiler
CC = avr-gcc

# Define the avrdude
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Define the hex file
$(HEX): $(PROJECT).elf
	avr-objcopy -O ihex $< $@

# Define the upload
upload: $(HEX)
	avrdude -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(HEX):i 

all: $(HEX)

clean:
	rm -f $(OBJ) $(PROJECT).elf $(HEX)