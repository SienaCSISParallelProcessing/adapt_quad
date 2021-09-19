# Makefile for adaptive quadrature
#
# Jim Teresco, CS 338 Williams College
# CS 341, Mount Holyoke College
# CS 400/CS 335, Siena College
#
CFILES=adapt_quad.c timer.c
OFILES=$(CFILES:.c=.o)
CC=gcc -Wall

adapt_quad:	$(OFILES)
	$(CC) -o adapt_quad $(OFILES) -lm

clean::
	/bin/rm -f adapt_quad $(OFILES)
