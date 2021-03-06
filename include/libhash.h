/*
 * libhash is a fast and efficient non-iterating hashmap library
 *
 * https://github.com/rohanrhu/libhash
 *
 * Licensed under MIT
 * Copyright (C) 2021, Oğuzhan Eroğlu (https://oguzhaneroglu.com/) <rohanrhu2@gmail.com>
 *
 */

#ifndef __LIBHASH_H__
#define __LIBHASH_H__

#ifndef LIBHASH_MAP_SIZE
#define LIBHASH_MAP_SIZE 256
#endif

typedef struct libhash_node libhash_node_t;
struct libhash_node {
    libhash_node_t* map[LIBHASH_MAP_SIZE];
    libhash_node_t* parent;
    void* value;
    int len;
};

typedef struct libhash libhash_t;
struct libhash {
    libhash_node_t* root;
};

libhash_t* libhash_init();
void libhash_free(libhash_t* hashmap);
libhash_node_t* libhash_set(libhash_t* hashmap, char* key, void* value);
void libhash_unset(libhash_t* hashmap, char* key);
libhash_node_t* libhash_get(libhash_t* hashmap, char* key);

libhash_node_t* libhash_node_init();
void libhash_node_free(libhash_node_t* node);
libhash_node_t* libhash_node_key(libhash_node_t* root, char* key);

#endif