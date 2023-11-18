CC             =  arm-none-eabi-gcc
CFLAGS         =  -c -mcpu=cortex-m4
OBJCOPY        =  arm-none-eabi-objcopy

SRC_FOLDER     =  src
SRC_DIR        =  ./$(SRC_FOLDER)/
INC_FOLDER     =  inc
INC_DIR        =  ./$(INC_FOLDER)/
BUILD_FOLDER   =  build
BUILD_DIR      =  ./$(BUILD_FOLDER)/

VPATH = src;inc;build

# Rules starts here
all: main.o startup.o led.o output.elf output.bin

# Generate Object Files
main.o: main.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $(BUILD_FOLDER)/$@
led.o: led.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $(BUILD_FOLDER)/$@
startup.o: startup.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $(BUILD_FOLDER)/$@

# Link the object files and generate .map file
output.elf:$(BUILD_FOLDER)/main.o $(BUILD_FOLDER)/startup.o $(BUILD_FOLDER)/led.o
	$(CC) -T linkerscript.ld -nostdlib $^ -o $(BUILD_DIR)$@ -Wl,-Map=$(BUILD_DIR)output.map 

# Generate Binary executable
output.bin:output.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)$^ $(BUILD_DIR)$@
output.hex:output.elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)$^ $(BUILD_DIR)$@

# Clean the repository from generated output 
clean:
	del /q .\$(BUILD_FOLDER)

load:
	openocd -f board/ti_ek-tm4c123gxl.cfg