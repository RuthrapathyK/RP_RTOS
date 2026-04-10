CC             =  arm-none-eabi-gcc
CFLAGS         =  -c -g -O0 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -Wextra -pedantic
OBJCOPY        =  arm-none-eabi-objcopy
OBJDUMP        =  arm-none-eabi-objdump

SRC_FOLDER     =  src
INC_FOLDER     =  inc
BUILD_FOLDER   =  build
BOARD_FOLDER   =  board
BUILD_DIR      =  ./$(BUILD_FOLDER)/

OPENOCD_INIT   =  -c 'reset init'
OPENOCD_HALT   =  -c 'reset halt'
OPENOCD_FLASH  =  -c 'flash write_image erase build/out.elf'
OPENOCD_RESUME =  -c 'reset resume'
OPENOCD_FLASHING_COMMANDS = $(OPENOCD_INIT) $(OPENOCD_HALT) $(OPENOCD_FLASH) #$(OPENOCD_RESUME) $(OPENOCD_INIT) 

VPATH = src;inc;build

# Recursively find all .c files in src/ folder and all subdirectories
SOURCES := $(shell powershell -Command "Get-ChildItem -Path '$(SRC_FOLDER)' -Filter '*.c' -Recurse | ForEach-Object { Write-Output $$_.FullName }")
OBJECTS = $(addprefix $(BUILD_FOLDER)/, $(notdir $(SOURCES:.c=.o)))

# Generic pattern rule: compile all .c files from any location in src folder and subdirectories
$(BUILD_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $@

$(BUILD_FOLDER)/%.o: $(SRC_FOLDER)/*/%.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $@

$(BUILD_FOLDER)/%.o: $(SRC_FOLDER)/*/*/%.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $@

$(BUILD_FOLDER)/%.o: $(SRC_FOLDER)/*/*/*/%.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $@

$(BUILD_FOLDER)/%.o: $(SRC_FOLDER)/*/*/*/*/%.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $< -o $@

# Rules starts here
build: clean $(OBJECTS) out.elf out.bin out.hex out.s

# Link the object files and generate .map file
out.elf: $(OBJECTS)
	$(CC) -T linkerscript.ld -nostdlib $^ -o $(BUILD_DIR)$@ -Wl,-Map=$(BUILD_DIR)out.map 

# Generate Binary executable
out.bin:out.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)$^ $(BUILD_DIR)$@
out.hex:out.elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)$^ $(BUILD_DIR)$@
out.s:out.elf
	$(OBJDUMP) -d $(BUILD_DIR)$^ > $(BUILD_DIR)$@


# Clean the repository from generated output 
clean:
	attrib +h $(BUILD_FOLDER)\.gitkeep 
	del /q .\$(BUILD_FOLDER)

flash:build
	openocd -f .\$(BOARD_FOLDER)\ti_ek-tm4c123gxl.cfg -c init $(OPENOCD_FLASHING_COMMANDS) -c reset -c shutdown