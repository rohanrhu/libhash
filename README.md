# `libhash`: a fast and efficient non-iterating hashmap library
Libhash is a fast and efficient non-iterating hashmap library

## Usage
Usage is easy and simple. You can look to `examples/` directory. You can build examples with `make` command.

### Including
```c
#include "libhash/include/libhash.h"
```

### Building

```bash
gcc -o application libhash/src/libhash.c application.c
```

### Simple Hashmap
Here is an example for simple hashmap.

```C
#include <stdio.h>

#include "libhash/include/libhash.h"

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
```

## UTF-8 Support
Default map size is `256` to support UTF-8 keys. You can downgrade it to `128` if you only want to use ASCII keys.

If you don't want UTF-8 support, just pass `CFLAGS+=-DLIBHASH_MAP_SIZE=128` to `make`. **It will reduce memory usage.**

```bash
make CFLAGS+=-DLIBHASH_MAP_SIZE=128
```

## Benchmark
There is a benchmark in `examples/benchmark` directory. You can just do:

```bash
cd examples/benchmark
make clean; make; ./benchmark
```

## Functions

### `libhash_t* libhash_init()`
Creates a hashmap.

### `libhash_node_t* libhash_set(libhash_t* hashmap, char* key, void* value)`
Sets a key-value pair and returns the node.

### `void libhash_unset(libhash_t* hashmap, char* key)`
Unsets a key-value pair.

### `libhash_node_t* libhash_get(libhash_t* hashmap, char* key)`
Gets the value of `key`.

### `void libhash_free(libhash_t* hashmap)`
Frees `hashmap`.

### `void libhash_node_free(libhash_node_t* node)`
Frees `node`.

## Types

### `libhash_t`
The hashmap type.

```C
typedef struct libhash libhash_t;
struct libhash {
    libhash_node_t* root;
};
```

### `libhash_node_t`

```C
typedef struct libhash_node libhash_node_t;
struct libhash_node {
    libhash_node_t* map[LIBHASH_MAP_SIZE];
    libhash_node_t* parent;
    void* value;
    int len;
};
```

## License

Copyright (c) 2021 Oğuzhan Eroğlu <rohanrhu2@gmail.com> (https://oguzhaneroglu.com). All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT>.