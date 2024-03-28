PROJECT = fs-firmware-v4-c_test

MCU = atmega2560
MCU_I2C = atmega328p
F_CPU = 16000000UL
PROGRAMMER = atmelice_isp

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(INCLUDES) -Wall -Os -c
LDFLAGS = -mmcu=$(MCU)


i2c: $(SRC)
	# Compile the i2c.c file without linking
	$(CC) $(CFLAGS) i2c/i2c.c -o build/i2c.o
	# Link the i2c.o file to create the i2c.elf file
	$(CC) $(LDFLAGS) build/i2c.o -o build/i2c.elf
	# Create the i2c.hex file from the i2c.elf file
	$(OBJCOPY) -O ihex build/i2c.elf build/i2c.hex
	# Upload the i2c.hex file to the microcontroller
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -U flash:w:build/i2c.hex:i

blink: $(SRC)
	# Compile the blink.c file without linking
	$(CC) $(CFLAGS) blink/blink.c -o build/blink.o
	# Link the blink.o file to create the blink.elf file
	$(CC) $(LDFLAGS) build/blink.o -o build/blink.elf
	# Create the blink.hex file from the blink.elf file
	$(OBJCOPY) -O ihex build/blink.elf build/blink.hex
	# Upload the blink.hex file to the microcontroller
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -U flash:w:build/blink.hex:i

i2c_master: $(SRC)
	# Compile the i2c_master.c file without linking
	$(CC) -mmcu=$(MCU_I2C) -DF_CPU=$(F_CPU) -I$(INCLUDES) -Wall -Os -c i2c_master/i2c.c -o build/i2c.o
	# Link the i2c_master.o file to create the i2c_master.elf file
	$(CC) -mmcu=$(MCU_I2C) build/i2c.o -o build/i2c.elf
	# Create the i2c_master.hex file from the i2c_master.elf file
	$(OBJCOPY) -O ihex build/i2c.elf build/i2c.hex
	# Upload the i2c.hex file to the microcontroller
	$(AVRDUDE) -p $(MCU_I2C) -c $(PROGRAMMER) -U flash:w:build/i2c.hex:i

clean:
	rm -f build/*.o build/*.elf build/*.hex
	
.PHONY: i2c blink i2c_master clean