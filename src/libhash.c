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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../include/libhash.h"

libhash_t* libhash_init() {
    libhash_t* hashmap = malloc(sizeof(libhash_t));
    hashmap->root = libhash_node_init();

    return hashmap;
}

void libhash_set(libhash_t* hashmap, char* key, void* value) {
    libhash_node_t* current = hashmap->root;
    
    int i = 0;
    unsigned char c;
    libhash_node_t* latest;

    ITERATE:
    
    for (; (c = key[i]) != '\0'; i++) {
        latest = current->map[c];
        
        if (!latest) {
            break;
        }

        current = latest;
    }
    
    i++;

    if (c == '\0') {
        goto END;
    }

    current->map[c] = libhash_node_init();
    current->map[c]->parent = current;
    current->len++;

    if (c != '\0') {
        current = current->map[c];
        goto ITERATE;
    }
    
    END:

    current->value = value;
}

void libhash_unset(libhash_t* hashmap, char* key) {
    libhash_node_t* current;
    libhash_node_t* to_remove;

    current = libhash_node_key(hashmap->root, key);

    if (!current) {
        return;
    }

    to_remove = current;
    current = current->parent;

    to_remove->value = NULL;
    to_remove->parent->len--;
    free(to_remove);

    ITERATE:
    
    if (!current) {
        goto END;
    }

    if (current->len == 0 && !current->value) {
        to_remove = current;
        current = current->parent;
        to_remove->parent->len--;
        free(to_remove);

        goto ITERATE;
    }

    END:;
}

libhash_node_t* libhash_get(libhash_t* hashmap, char* key) {
    libhash_node_t* node = libhash_node_key(hashmap->root, key);
    return node;
}

libhash_node_t* libhash_node_init() {
    libhash_node_t* node = malloc(sizeof(libhash_node_t));
    memset(node, 0, sizeof(libhash_node_t));

    return node;
}

libhash_node_t* libhash_node_key(libhash_node_t* root, char* key) {
    libhash_node_t* current = root;
    
    libhash_node_t* result = NULL;
    
    for (int i=0; key[i] != '\0'; i++) {
        current = current->map[(unsigned char) key[i]];
        
        if (!current && key[i] != '\0') {
            return NULL;
        }
        
        if (!current) {
            break;
        }

        result = current;
    }
    
    return result;
}