# Makefile for error
NAME=error

# Compiler
CPP = g++

# Directives for the compiler
# -c: the output is an object file; the linking stage is not done.
# -g: debug
# -Wall: all warnings
# -ansi: standard language
# -02: optimization level
CFLAGS = -c -g  -Wall -ansi -O2

# Objects
OBJECTS= $(NAME).o

# Includes
INCLUDES = $(NAME).hpp ../includes/macros.hpp

# Predefined macros 
#
# $@: name of the target
# $^: all the dependencies
# $<: first dependency
#
#######################################################

# Main rule

all: $(OBJECTS)


# Error recovery functions 
$(NAME).o: $(NAME).cpp $(INCLUDES)
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<
	@echo



#######################################################
# Auxiliary files are deleted
.PHONY: clean
clean: 
	@echo
	@echo "Deleting in subdirectory error"
	@rm -f $(OBJECTS) *~ 
	@echo

