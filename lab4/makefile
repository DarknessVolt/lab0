# Name: Allan Huidobro
# Project: Lab 1

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLES= dining-p launch-philosophers
SRC=%.c
OBJ=%.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXECUTABLES)


# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
dining-p:
	$(CC) $(CFLAGS) -c dining.c
	$(CC) $(CFLAGS) -lpthread -lrt -o $@ dining.o

launch-philosophers:
	$(CC) $(CFLAGS) -c dininglaunch.c
	$(CC) $(CFLAGS) -lpthread -lrt -o $@ dininglaunch.o
# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLES) dining.o dininglaunch.o
