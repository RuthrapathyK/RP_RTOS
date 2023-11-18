CC             =  arm-none-eabi-gcc
CFLAGS         =  -c -mcpu=cortex-m4
OBJCOPY        =  arm-none-eabi-objcopy

SRC_FOLDER     =  src
INC_FOLDER     =  inc
BUILD_FOLDER   =  build
BUILD_DIR      =  ./$(BUILD_FOLDER)/

OPENOCD_INIT   =  -c 'reset init'
OPENOCD_HALT   =  -c 'reset halt'
OPENOCD_FLASH  =  -c 'flash write_image erase build/out.elf'
OPENOCD_RESUME =  -c 'reset resume'
OPENOCD_FLASHING_COMMANDS = $(OPENOCD_INIT) $(OPENOCD_HALT) $(OPENOCD_FLASH) #$(OPENOCD_RESUME) $(OPENOCD_INIT) 

VPATH = src;inc;build

# Rules starts here
build: clean main.o startup.o led.o out.elf out.bin out.hex

# Generate Object Files
main.o: main.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $(BUILD_FOLDER)/$@
led.o: led.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $(BUILD_FOLDER)/$@
startup.o: startup.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $(BUILD_FOLDER)/$@

# Link the object files and generate .map file
out.elf:$(BUILD_FOLDER)/main.o $(BUILD_FOLDER)/startup.o $(BUILD_FOLDER)/led.o
	$(CC) -T linkerscript.ld -nostdlib $^ -o $(BUILD_DIR)$@ -Wl,-Map=$(BUILD_DIR)output.map 

# Generate Binary executable
out.bin:out.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)$^ $(BUILD_DIR)$@
out.hex:out.elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)$^ $(BUILD_DIR)$@

# Clean the repository from generated output 
clean:
	DEL "$(BUILD_FOLDER)\*.o" /S /Q
	DEL "$(BUILD_FOLDER)\*.bin" /S /Q
	DEL "$(BUILD_FOLDER)\*.elf" /S /Q
	DEL "$(BUILD_FOLDER)\*.hex" /S /Q
	DEL "$(BUILD_FOLDER)\*.map" /S /Q

flash:build
	openocd -f board/ti_ek-tm4c123gxl.cfg -c init $(OPENOCD_FLASHING_COMMANDS) -c reset -c shutdown
	