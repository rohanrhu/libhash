/*
 * libhash is a fast and efficient non-iterating hashmap library
 *
 * https://github.com/rohanrhu/libhash
 *
 * Licensed under MIT
 * Copyright (C) 2021, Oğuzhan Eroğlu (https://oguzhaneroglu.com/) <rohanrhu2@gmail.com>
 *
 */

#pragma once

typedef struct libhash_node libhash_node_t;
struct libhash_node {
    libhash_node_t* map[256];
    libhash_node_t* parent;
    void* value;
    int len;
};

typedef struct libhash libhash_t;
struct libhash {
    libhash_node_t* root;
};

extern libhash_t* libhash_init();
extern void libhash_free(libhash_t* hashmap);
extern libhash_node_t* libhash_set(libhash_t* hashmap, char* key, void* value);
extern void libhash_unset(libhash_t* hashmap, char* key);
extern libhash_node_t* libhash_get(libhash_t* hashmap, char* key);

extern libhash_node_t* libhash_node_init();
extern void libhash_node_free(libhash_node_t* node);
extern libhash_node_t* libhash_node_key(libhash_node_t* root, char* key);

extern uint32_t libhash_hash32(char* str);