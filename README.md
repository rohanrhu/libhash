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

    libhash_node_t* alien = libhash_get(movies, "Alien");
    libhash_node_t* prometheus = libhash_get(movies, "Prometheus");

    printf("Alien: %s\n", alien->value);
    printf("Prometheus: %s\n", prometheus->value);

    return 0;
}
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

### `void libhash_set(libhash_t* hashmap, char* key, void* value)`
Sets a key-value pair.

### `void libhash_unset(libhash_t* hashmap, char* key)`
Unsets a key-value pair.

### `libhash_node_t* libhash_get(libhash_t* hashmap, char* key)`
Gets the value of `key`.

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
    libhash_node_t* map[128];
    libhash_node_t* parent;
    void* value;
    int len;
};
```

## License
MIT