NAME=interpreter

# Compiler
CPP = g++

# Directives for the compiler
# -c: the output is an object file, the linking stage is not done.
# -g: debug
# -Wall: all warnings
# -ansi: standard language
# -02: optimization level
CFLAGS = -c -g  -Wall -ansi -O2

# Directive for flex's library
LFLAGS = -lfl
#LFLAGS = -ll

# Objects
OBJECTS= $(NAME).o
OBJECTS-PARSER = parser/*.o
OBJECTS-ERROR = error/*.o
OBJECTS-TABLE = table/*.o  # New in example 7
OBJECTS-AST = ast/*.o  # New in example 16


# Includes
# MODIFIED in example 7: ./table/table.hpp
# MODIFIED in example 10: ./table/init.hpp
# MODIFIED in example 16: ./ast/ast.hpp
INCLUDES = ./parser/interpreter.tab.h ./error/error.hpp \
			./table/table.hpp \
			./table/init.hpp \
			./ast/ast.hpp

#######################################################
# Predefined macros 
#
# $@: name of the target
# $^: all the dependencies
# $<: first dependency
#
#######################################################


#Modified in examples 7, 16
$(NAME).exe :  parser-dir error-dir table-dir ast-dir $(OBJECTS)
	@echo "Generating " $(NAME).exe
	@$(CPP) $(OBJECTS) $(OBJECTS-PARSER) $(OBJECTS-ERROR)  $(OBJECTS-TABLE)  $(OBJECTS-AST) \
	$(LFLAGS) -o $(NAME).exe 


# Main program
$(NAME).o: $(NAME).cpp parser-dir ast-dir $(INCLUDES)
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<
	@echo

# 
parser-dir:
	@echo "Accessing directory parser" 
	@echo
	@make -C parser/
	@echo

error-dir:
	@echo "Accessing directory error" 
	@echo
	@make -C error/ 
	@echo

# New in example 7
table-dir:
	@echo "Accessing directory table" 
	@echo
	@make -C table/ 
	@echo


# New in example 16
ast-dir:
	@echo "Accessing directory ast" 
	@echo
	@make -C ast/ 
	@echo


#######################################################
$(NAME).output: 
	@echo "Generating: " $@
	@make -C parser/ $@
	@echo


#######################################################
# Generate the documentation
doc: Doxyfile
	doxygen

#######################################################
# Auxiliary files and html directory are deleted
# Modified in examples 7, 16
.PHONY: clean
clean: 
	@echo "Deleting html"
	@rm -rf html 
	@echo "Deleting " $(OBJECTS)  $(NAME).exe  *~ 
	@rm -f $(OBJECTS) $(NAME).exe *~ 
	@echo
	@make -C parser/ clean 
	@echo
	@make -C error/ clean
	@echo
	@make -C table/ clean
	@echo
	@make -C ast/ clean
	@echo


