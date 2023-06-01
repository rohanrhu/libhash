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
#include <stdint.h>

#include "../include/libhash.h"

extern uint32_t libhash_hash32(char* str) {
    uint32_t hash = 0;

    int remaining = 4;
    int prev = 0;

    for (int i=0; str[i] != '\0'; i++) {
        remaining--;
        int c = str[i] & 0b01111111;
        uint8_t mask = ((c % 255) << (((((prev % 2) != 0) ? prev: 1) * i * c) % 7));
        *(((unsigned char *)(&hash)) + ((i * c + prev) % 3)) = ((prev % 2) == 0)
                                                ? mask | prev
                                                : mask & prev;
        prev = (i * c) % 7;
    }

    for (int i=remaining; i > 0; i--) {
        *(((unsigned char *)(&hash)) + ((4 - i) % 4)) = str[i % ((4 - i) % (4 - remaining))];
    }

    return hash;
}

libhash_t* libhash_init() {
    libhash_t* hashmap = malloc(sizeof(libhash_t));
    hashmap->root = libhash_node_init();

    return hashmap;
}

extern libhash_node_t* libhash_set(libhash_t* hashmap, char* str_key, void* value) {
    uint32_t scalar_key = libhash_hash32(str_key);
    char* key = (char *) (&scalar_key);
    
    libhash_node_t* current = hashmap->root;
    
    int i = 0;
    unsigned char c;
    libhash_node_t* latest;

    ITERATE:
    
    for (; i < 4; i++) {
        c = key[i];
        latest = current->map[c];
        
        if (!latest) {
            break;
        }

        current = latest;
    }
    
    i++;

    if (!current->map[c]) {
        current->map[c] = libhash_node_init();
    }
    current->map[c]->parent = current;
    current->len++;

    current = current->map[c];

    if (i < 4) {
        goto ITERATE;
    }
    
    END:

    current->value = value;

    return current;
}

extern void libhash_unset(libhash_t* hashmap, char* str_key) {
    uint32_t scalar_key = libhash_hash32(str_key);
    char* key = (char *) (&scalar_key);
    
    libhash_node_t* current;
    libhash_node_t* to_remove;

    current = libhash_node_key(hashmap->root, str_key);

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

extern libhash_node_t* libhash_get(libhash_t* hashmap, char* str_key) {
    uint32_t scalar_key = libhash_hash32(str_key);
    char* key = (char *) (&scalar_key);
    
    libhash_node_t* node = libhash_node_key(hashmap->root, str_key);
    return node;
}

extern libhash_node_t* libhash_node_init() {
    libhash_node_t* node = malloc(sizeof(libhash_node_t));
    memset(node, 0, sizeof(libhash_node_t));

    return node;
}

extern libhash_node_t* libhash_node_key(libhash_node_t* root, char* str_key) {
    uint32_t scalar_key = libhash_hash32(str_key);
    char* key = (char *) (&scalar_key);
    
    libhash_node_t* current = root;
    
    libhash_node_t* result = NULL;
    
    for (int i=0; i < 4; i++) {
        current = current->map[(unsigned char) key[i]];
        
        if (!current) {
            return NULL;
        }
        
        if (!current) {
            break;
        }

        result = current;
    }
    
    return result;
}

extern void libhash_free(libhash_t* hashmap) {
    libhash_node_free(hashmap->root);
    free(hashmap);
}

static void free_node(libhash_node_t* node) {
    for (int i=0; i < (sizeof(node->map) / (sizeof(libhash_node_t))); i++) {
        free_node(node->map[i]);
    }
    
    node->value = NULL;
    free(node);
}

extern void libhash_node_free(libhash_node_t* node) {
    free_node(node);
}