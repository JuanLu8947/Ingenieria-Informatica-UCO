# Makefile for ast
NAME=ast

# Compiler
CPP = g++

# Directives for the compiler
# -c: the output is an object file, the linking stage is not done.
# -g: debug
# -Wall: all warnings
# -ansi: standard language
# -02: optimization level
CFLAGS = -c -g  -Wall -ansi -O2

# Objects
OBJECTS= $(NAME).o

# Includes
INCLUDES = $(NAME).hpp \
			../parser/interpreter.tab.h \
			../includes/macros.hpp ../error/error.hpp \
			../table/table.hpp  ../table/numericConstant.hpp \
			../table/builtinParameter0.hpp ../table/builtinParameter1.hpp ../table/builtinParameter2.hpp

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
# Auxiliary files directory are deleted
.PHONY: clean
clean: 
	@echo
	@echo "Deleting in subdirectory ast"
	@rm -f $(OBJECTS) *~ 
	@echo

