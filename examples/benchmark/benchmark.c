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
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "../../include/libhash.h"

char* random_string(int size) {
    char* string = malloc(size+1);
    string[size] = '\0';
    
    for (int i=0; i < size; i++) {
        string[i] = 33 + ((rand() % 95) - 33);
    }

    return string;
}

int main() {
    srand(time(NULL));

    struct timeval t0, t1;
    gettimeofday(&t0, NULL);
    
    libhash_t* movies = libhash_init();

    for (int i=0; i < 10000; i++) {
        libhash_set(movies, random_string(10), random_string(10));
    }

    gettimeofday(&t1, NULL);
    long int usecs = (t1.tv_sec * 1000000 + t1.tv_usec) - (t0.tv_sec * 1000000 + t0.tv_usec);
    printf("\033[1;32m%ld\033[0mus elapsed.\n", usecs);
    printf("\033[1;32m%.2f\033[0ms elapsed.\n", usecs/1000000.0);
    printf("... to set 1000000 key=>value pairs.\n");

    libhash_set(movies, "Alien", "The best movie ever!");
    libhash_set(movies, "Prometheus", "The worst movie ever!");
    
    gettimeofday(&t0, NULL);

    libhash_node_t* alien = libhash_get(movies, "Alien");

    gettimeofday(&t1, NULL);
    usecs = (t1.tv_sec * 1000000 + t1.tv_usec) - (t0.tv_sec * 1000000 + t0.tv_usec);
    printf("\033[1;32m%ld\033[0mus elapsed.\n", usecs);
    printf("\033[1;32m%.2f\033[0ms elapsed.\n", usecs/1000000.0);
    printf("... to get a key=>value pair within 1000000 items.\n");

    alien && printf("Alien: %s\n", alien->value);

    libhash_free(movies);

    return 0;
}