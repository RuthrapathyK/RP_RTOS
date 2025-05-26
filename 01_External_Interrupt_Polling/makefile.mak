CC             =  arm-none-eabi-gcc
CFLAGS         =  -c -g -O0 -mcpu=cortex-m4
OBJCOPY        =  arm-none-eabi-objcopy
OBJDUMP        =  arm-none-eabi-objdump

SRC_FOLDER     =  src
INC_FOLDER     =  inc
BUILD_FOLDER   =  build
BUILD_DIR      =  ..\$(BUILD_FOLDER)

OPENOCD_INIT   =  -c 'reset init'
OPENOCD_HALT   =  -c 'reset halt'
OPENOCD_FLASH  =  -c 'flash write_image erase build/out.elf'
OPENOCD_RESUME =  -c 'reset resume'
OPENOCD_FLASHING_COMMANDS = $(OPENOCD_INIT) $(OPENOCD_HALT) $(OPENOCD_FLASH) #$(OPENOCD_RESUME) $(OPENOCD_INIT) 

VPATH = src;inc;build

# Rules starts here
build: clean main.o startup.o led.o out.elf out.bin out.hex out.s

# Generate Object Files
main.o: main.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $(BUILD_DIR)/$@
led.o: led.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $(BUILD_DIR)/$@
startup.o: startup.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $(BUILD_DIR)/$@

# Link the object files and generate .map file
out.elf:$(BUILD_DIR)/main.o $(BUILD_DIR)/startup.o $(BUILD_DIR)/led.o
	$(CC) -T linkerscript.ld -nostdlib $^ -o $(BUILD_DIR)\$@ -Wl,-Map=$(BUILD_DIR)\out.map 

# Generate Binary executable
out.bin:out.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)\$^ $(BUILD_DIR)\$@
out.hex:out.elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)\$^ $(BUILD_DIR)\$@
out.s:out.elf
	$(OBJDUMP) -d $(BUILD_DIR)\$^ > $(BUILD_DIR)\$@


# Clean the repository from generated output 
clean:
	attrib +h $(BUILD_DIR)\.gitkeep 
	del /q $(BUILD_DIR)

flash:build
	openocd -f board/ti_ek-tm4c123gxl.cfg -c init $(OPENOCD_FLASHING_COMMANDS) -c reset -c shutdown
	