# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

# List of your source files
SRCS = main.c encryption.c math_tools.c user.c audit.c logs.c

# List of object files (replaces .c with .o)
OBJS = $(SRCS:.c=.o)

# Name of your final executable
TARGET = security_suite

# Default rule
all: $(TARGET)

# Rule to link the program
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile each .c file into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove temporary files
clean:
	rm -f $(OBJS) $(TARGET)