# Specify the microcontroller and CPU frequency
MCU = atmega32
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
TARGET = main
SOURCES = $(wildcard *.c)  # Automatically includes all .c files in the directory
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET).hex

# Rule to link object files and create the ELF file
$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# Rule to convert ELF file to HEX file
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Rule to compile C files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up build files
clean:
	rm -f $(TARGET).elf $(TARGET).hex $(OBJECTS)

