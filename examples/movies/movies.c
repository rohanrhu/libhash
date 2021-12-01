/*
 * libhash is a fast and efficient non-iterating hashmap library
 *
 * https://github.com/rohanrhu/libhash
 *
 * Licensed under MIT
 * Copyright (C) 2021, Oğuzhan Eroğlu (https://oguzhaneroglu.com/) <rohanrhu2@gmail.com>
 *
 */

#define _GNU_SOURCE

#include <stdio.h>

#include "../../include/libhash.h"

int main() {
    libhash_t* movies = libhash_init();
    libhash_set(movies, "Alien", "The best movie ever!");
    libhash_set(movies, "Prometheus", "The worst movie ever!");
    libhash_set(movies, "こんにちは世界", "Hello World!");

    libhash_node_t* alien = libhash_get(movies, "Alien");
    libhash_node_t* prometheus = libhash_get(movies, "Prometheus");
    libhash_node_t* hello = libhash_get(movies, "こんにちは世界");

    hello && printf("こんにちは世界: %s\n", hello->value);
    alien && printf("Alien: %s\n", alien->value);
    prometheus && printf("Prometheus: %s\n", prometheus->value);

    libhash_free(movies);

    return 0;
}