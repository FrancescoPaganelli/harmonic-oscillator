################################################################################
#
# Makefile to compile and link C programs
#
# Version valid for Linux machines
#
# "make" compiles and links the specified main programs and modules
# using the specified libraries (if any), and produces the executables
# 
# "make clean" removes all files created by "make"
#
# Dependencies on included files are automatically taken care of
#
################################################################################

all: rmxeq mkdep mkxeq
.PHONY: all


# main programs and required modules 

MAIN = thermalization xx_correlator energy_evaluation energy_evaluation_copy

RANDOM = ranlxs ranlxd gauss

START = start utils

ACTION = action

CORRELATORS = correlation

EXTRAS =

METROPOLIS = metropolis

JACKKNIFE = jackknife

MODULES = $(RANDOM) $(START) $(EXTRAS) $(ACTION) $(METROPOLIS) $(CORRELATORS) $(JACKKNIFE)


# search path for modules

MDIR = ../modules

VPATH = $(MDIR)/random:$(MDIR)/start:$(MDIR)/extras:$(MDIR)/action:$(MDIR)/metropolis:$(MDIR)/correlators:$(MDIR)/jackknife


# additional include directories

INCPATH = ../include


# additional libraries to be included 
 
LIBS = m

LIBPATH =


# scheduling and optimization options (such as -DSSE -DSSE2 -DP4)
 
CFLAGS = -std=c89 -pedantic -fstrict-aliasing \
         -Wall -Wno-long-long -Werror -O 
 

############################## do not change ###################################

SHELL=/bin/bash

CC=gcc

PGMS= $(MAIN) $(MODULES)

INCDIRS = $(addprefix -I,$(INCPATH))

OBJECTS = $(addsuffix .o,$(MODULES))

LDFLAGS = $(addprefix -L,$(LIBPATH)) $(addprefix -l,$(LIBS))

-include $(addsuffix .d,$(PGMS))


# rule to make dependencies

$(addsuffix .d,$(PGMS)): %.d: %.c Makefile
	@ $(CC) -MM -ansi $(INCDIRS) $< -o $@


# rule to compile source programs

$(addsuffix .o,$(PGMS)): %.o: %.c Makefile
	$(CC) $< -c $(CFLAGS) $(INCDIRS) -o $@


# rule to link object files

$(MAIN): %: %.o $(OBJECTS) Makefile
	$(CC) $< $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@


# produce executables

mkxeq: $(MAIN)


# remove old executables and old error log file

rmxeq:
	@ -rm -f $(MAIN); \
        echo "delete old executables"		


# make dependencies

mkdep:  $(addsuffix .d,$(PGMS))
	@ echo "generate tables of dependencies"


# clean directory 

clean:
	@ -rm -rf *.d *.o .tmp $(MAIN)
.PHONY: clean

################################################################################
