# MAKEFILE for parser

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

# The fast lexical analyser generator
LEX = flex

#GNU Project parser generator (yacc replacement)
YACC= bison 

# Options
# -d: the file y.tab.h is generated
# -y: yacc compatibility --> y.tab.c y.tab.h (OPTIONAL)
# -t: debug
# -g: the file NAME.gv (or NAME.dot)  is generated; 
#     this file can be seen on the screen using 
#       dot -Tx11 NAME.gv
#       Alternatives 
#	 	dot -TXXX NAME.gv -o NAME.XXX
#	    where XXX can be: gif, pdf, png, ps, svg
# -v  the file NAME.output is generated (OPTIONAL)
YFLAGS = -d -t -g

# Objects
OBJECTS= $(NAME).tab.o lex.yy.o 

# Includes
# MODIFIED in example 7: ../table/table.hpp  ../table/numericVariable.hpp
# MODIFIED in example 10: ../table/init.hpp
# MODIFIED in example 11: ../table/numericConstant.hpp
# MODIFIED in example 13: ../table/builtinParameter1.hpp
# MODIFIED in example 14: ../table/builtinParameter0.hpp ../table/builtinParameter2.hpp
# MODIFIED in example 15: ./includes/Value.hpp
INCLUDES = ../error/error.hpp ../includes/macros.hpp \
			../table/table.hpp  ../table/numericVariable.hpp \
			../table/init.hpp \
			../table/numericConstant.hpp \
			../table/builtinParameter1.hpp \
			../table/builtinParameter0.hpp	../table/builtinParameter2.hpp 


#######################################################

# Regla principal

all: $(OBJECTS)


# Subreglas

# Lexical analyzer
# -Wno-unused-function, -Wno-sign-compare: these error messages are not displayed
lex.yy.o:  lex.yy.c $(NAME).tab.h
	$(CPP) $(CFLAGS)  -Wno-unused-function  -Wno-sign-compare $<

lex.yy.c: $(NAME).l $(NAME).tab.h $(INCLUDES)
	@echo "Generating: " $@
	@$(LEX) $<
	@echo

# Parser
$(NAME).tab.o: $(NAME).tab.c  $(NAME).tab.h $(INCLUDES)
	@echo "Compiling: " $<
	@$(CPP) $(CFLAGS) $<
	@echo

$(NAME).tab.c $(NAME).tab.h: $(NAME).y $(INCLUDES)
	@echo "Generating: " $(NAME).tab.c $(NAME).tab.h
	@$(YACC) $(YFLAGS) $< 
	@echo



#######################################################
# Generate the output file to show conflicts, if they exist
$(NAME).output: $(NAME).y $(INCLUDES) 
	@echo "Generating: " $@
	@$(YACC) -v $< 
	@echo


#######################################################
# Auxiliary files directory are deleted
.PHONY: clean
clean: 
	@echo
	@echo "Deleting in subdirectory parser"
	@rm -f $(OBJECTS) $(NAME).tab.[ch] lex.yy.c $(NAME).gv $(NAME).dot $(NAME).output *~ 
	@echo



