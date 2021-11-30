#
# libhash is a fast and efficient non-iterating hashmap library
#
# https://github.com/rohanrhu/libhash
#
# Licensed under MIT
# Copyright (C) 2021 Oğuzhan Eroğlu (https://oguzhaneroglu.com/) <rohanrhu2@gmail.com>
#

CC = gcc
CL = ld

CFLAGS = -std=c99 \
		 -I. \
		 -g \
		 -lm

LDFLAGS =

SOURCES = $(shell find . -wholename "./src/*.c")
HEADERS = $(shell find . -wholename "./include/*.h")
OBJECTS = $(notdir $(SOURCES:.c=.o))
RM = rm -rf

.PHONY: clean

all: libhash.o

libhash.o:
	$(CC) -c -o _libhash.o src/libhash.c $(CFLAGS) $(LDFLAGS)
	$(CL) -r _libhash.o -o libhash.o $(LDFLAGS)
	$(RM) _libhash.o

clean:
	make clean -C examples/movies
	$(RM) $(OBJECTS) _libhash.o