CC=g++
CFLAGS=-O2 -Winit-self -Wmain -pedantic -Wall -m64 -std=c++11 -Iaux
LDFLAGS=-s -lglfw -lX11 -lXrandr -lXinerama -ldl -lpthread -lGL
OBJDIR=build
SRC_DIR=src
AUX_DIR=aux
DEST=$(OBJDIR)/CoreBSP

# Source and object files
SRCS=$(SRC_DIR)/main.cpp $(SRC_DIR)/Quake3Bsp.cpp $(SRC_DIR)/w_init.cpp $(AUX_DIR)/glad.c
OBJS=$(OBJDIR)/main.o $(OBJDIR)/Quake3Bsp.o $(OBJDIR)/w_init.o $(OBJDIR)/glad.o

# Target
TARGET=$(DEST)

# Default target
all: $(TARGET)

$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(AUX_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Clean build directory
clean:
	rm -rf $(OBJDIR)

# Run the application
run: $(TARGET)
	./$(TARGET) maps/Level.bsp

.PHONY: all clean run
