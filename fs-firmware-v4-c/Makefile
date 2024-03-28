# Define the project name
PROJECT = fs-firmware-v4-c

# Define the microcontroller
MCU = atmega2560

# Define the clock frequency
F_CPU = 16000000UL

# Define the programmer
PROGRAMMER = atmelice_isp


INCLUDE_DIRS = -I include

INCLUDE := $(shell find . -type f -name '*.h')
SRC := $(shell find . -type f -name '*.c')

# Define the include files
# INCLUDES = $(wildcard *.h)

# Define the compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(INCLUDE_DIRS) -Wall -Os

# Define the linker flags
LDFLAGS = -mmcu=$(MCU) $(INCLUDE)

# Define the object files
OBJ = $(SRC:.c=.o)

# Define the hex file
HEX = $(PROJECT).hex

# Define the compiler
CC = avr-gcc

# Compile the source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link the object files to the elf file
$(PROJECT).elf: $(OBJ)
	$(CC) $(LDFLAGS) $< -o $@ 

# Create the hex file from elf file
$(HEX): $(PROJECT).elf
	avr-objcopy -O ihex $< $@

compile: $(SRC)
	$(CC) $(CFLAGS) $^  -o $(PROJECT).elf

# Upload the hex file to the microcontroller
upload: $(HEX)
	avrdude -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(HEX):i 

all: $(HEX)

clean:
	rm -f $(OBJ) $(PROJECT).elf $(HEX)
