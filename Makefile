#
# Alambix user Makefile
#
 
# Alambix install directory
ALAMBIX_DIR := $(realpath /home/evan/Documents/PMU/Projet_Alambix/alambix-v0.2.4)
 
# Alambix user interface
ALAMBIX_UI := original
 
# Program name
PROG := alambix
 
# Compiler to use
CC := gcc
 
# Source files
SRC := main.c
 
# File remove tool
RM := rm -f
 
#
# Generic part of the Makefile
#
OBJ := $(SRC:.c=.o)
 
# Alambix specific Makefile
null :=#
esc_space = $(subst $(null) $(null),\ ,$1)
ALAMBIX_PATH := $(call esc_space,$(ALAMBIX_DIR))
-include $(ALAMBIX_PATH)/make/Alambix.mk
 
# Makefile rules
.PHONY: all clean
 
all: $(PROG)
 
.c.o:
	$(CC) -c $(CCFLAGS) $< -o $@
 
$(PROG): $(OBJ)
	$(CC) $(OBJ) -o $(PROG) $(LDFLAGS)
 
clean:
	$(RM) $(PROG) *.o core
