EXEC = ./$(TARGET)
ifeq ($(OS),Windows_NT)
    EXEC = $(TARGET).exe
endif
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Source files
SRCS = main_trab_est.c paciente_func.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = programas_c

# Phony targets
.PHONY: all compile run clean

# Default target (compile and run)
all: compile run

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Run the executable  ; valgrind --leak-check=full antes do ./target para analizar a memoria usada -> necessario instalacao X so isso ja vale uns 40 pontos hein :)
run: $(TARGET)
	./$(TARGET) 

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executables
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
