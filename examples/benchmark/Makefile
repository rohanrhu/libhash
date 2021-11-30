#
# libhash is a lightweight WebSocket library for C
#
# https://github.com/rohanrhu/libhash
#
# Licensed under MIT
# Copyright (C) 2020, Oğuzhan Eroğlu (https://oguzhaneroglu.com/) <rohanrhu2@gmail.com>
#

CC = gcc
CL = ld

CFLAGS = -std=c99 \
		 -I. \
		 -g \
		 -lm

LDFLAGS =

LIBHASH_SOURCES = $(filter-out $(shell find ../../ -path "*/examples/*"), $(shell find ../../ -name "*.c"))
LIBHASH_HEADERS = $(filter-out $(shell find ../../ -path "*/examples/*"), $(shell find ../../ -name "*.h"))
LIBHASH_OBJ = ../../libhash.o
SOURCE = benchmark.c
EXECUTABLE = $(SOURCE:.c=)

.PHONY: clean libhash

all: $(EXECUTABLE)

libhash:
	make -C ../../

clean:
	$(RM) $(EXECUTABLE) $(LDFLAGS)

$(EXECUTABLE): libhash $(LIBHASH_OBJ)
	$(CC) -o $@ $(SOURCE) $(LIBHASH_OBJ) $(CFLAGS) $(LDFAGS)