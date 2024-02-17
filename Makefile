#############################################################
# 	Advanced Programming Course Assignment 2 Makefile		#
# 	Authors: Roy Simanovich and Almog Shor (c) 2024			#
# 	Description: This Makefile is used to compile the HW	#
# 				Date: 2024-02								#
# 			Course: Advanced Programming					#
# 				Assignment: 2								#
# 				Compiler: gcc								#
# 				OS: Linux									#
# 			IDE: Visual Studio Code							#
##############################################################

# Use the gcc compiler.
CC = gcc

# Flags for the compiler.
CFLAGS = -Wall -Wextra -Werror -std=c99 -g -pedantic -I$(SOURCE_PATH)

# Flags for the linker.
LDFLAGS = -pthread -lm

# Command to remove files.
RM = rm -f

# Constants for the source, object and include paths.
SOURCE_PATH = sources
OBJECT_PATH = objects
INCLUDE_PATH = include

# Variables for the source, object and header files.
SOURCES = $(wildcard $(SOURCE_PATH)/*.c)
HEADERS = $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS = $(subst sources/,objects/,$(subst .c,.o,$(SOURCES)))

# Variable for the object files.
OBJECTS_GEN = generator.o
OBJECTS_CNT = prime_counter.o Queue.o
OBJECTS_CNT_SIMPLE = prime_counter_no_threads.o
OBJ_FILES_GEN = $(addprefix $(OBJECT_PATH)/, $(OBJECTS_GEN))
OBJ_FILES_CNT = $(addprefix $(OBJECT_PATH)/, $(OBJECTS_CNT))
OBJ_FILES_CNT_SIMPLE = $(addprefix $(OBJECT_PATH)/, $(OBJECTS_CNT_SIMPLE))

# Variables for the names of the executables.
EXECUTABLES = generator prime_counter prime_counter_no_threads

# Phony targets - targets that are not files but commands to be executed by make.
.PHONY: all default clean

# Default target - compile everything and create the executables and libraries.
all: $(EXECUTABLES)

# Alias for the default target.
default: all


############
# Programs #
############

# Compile the generator Program.
generator: $(OBJ_FILES_GEN)
	$(CC) $(CFLAGS) -o $@ $^

# Compile the prime_counter Program (with threads).
prime_counter: $(OBJ_FILES_CNT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Compile the prime_counter_no_threads Program (without threads).
prime_counter_no_threads: $(OBJ_FILES_CNT_SIMPLE)
	$(CC) $(CFLAGS) -o $@ $^

################
# Object files #
################

# Compile all the C files that are in the source directory into object files that are in the object directory.
$(OBJECT_PATH)/%.o: $(SOURCE_PATH)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


#################
# Cleanup files #
#################

# Remove all the object files, shared libraries and executables.
clean:
	$(RM) $(OBJECT_PATH)/*.o *.so $(EXECUTABLES)