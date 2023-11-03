CFLAGS = -ansi -pedantic -Wall -Wextra -O3 -ffast-math
LDFLAGS = -Wl,--copy-dt-needed-entries -lSDL2 -lSDL2_image -lABC -lGL -lkazmath

GLAD_DIR=glad

SRC_DIR=src
BUILD_DIR=build

# GLAD into an object file once, so that it doesn't need to be compiled every
# single time.
$(GLAD_DIR)glad.o: $(GLAD_DIR)glad.c
	gcc -c $(GLAD_DIR)glad. -o $(GLAD_DIR)glad.o

$(BUILD_DIR)/main: $(SRC_DIR)/main.c $(GLAD_DIR)/glad.o
	gcc $(CFLAGS) $(SRC_DIR)/*.c $(GLAD_DIR)/glad.o -o $(BUILD_DIR)/main $(LDFLAGS)

$(BUILD_DIR)/main_test: $(SRC_DIR)/main.c $(GLAD_DIR)/glad.o
	gcc $(CFLAGS) $(SRC_DIR)/*.c $(GLAD_DIR)/glad.o -o $(BUILD_DIR)/main_test\
		$(LDFLAGS) -DDEBUG

$(BUILD_DIR)/main_gdb: $(SRC_DIR)/main.c $(GLAD_DIR)/glad.o
	gcc -g $(CFLAGS) $(SRC_DIR)/*.c $(GLAD_DIR)/glad.o -o $(BUILD_DIR)/main_gdb\
		$(LDFLAGS) -DDEBUG

.PHONY: run test build gdb clean

run: $(BUILD_DIR)/main
	$(BUILD_DIR)/main
	rm -rf $(BUILD_DIR)/main

test: $(BUILD_DIR)/main_test
	$(BUILD_DIR)/main_test
	rm -rf $(BUILD_DIR)/main_test

build: $(BUILD_DIR)/main
	cp *.frag $(BUILD_DIR)/
	cp *.vert $(BUILD_DIR)/
	cp *.png $(BUILD_DIR)/
	cp *.jpg $(BUILD_DIR)/
	cp *.obj $(BUILD_DIR)/

gdb: $(BUILD_DIR)/main_gdb
	gdb $(BUILD_DIR)/main_gdb

clean:
	rm -rf $(BUILD_DIR)/*
