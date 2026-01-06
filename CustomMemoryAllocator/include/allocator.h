#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

/*
 * Block layout in memory:
 *
 *  | header | payload |
 *
 * The allocator returns a pointer to the payload.
 */

typedef struct BlockHeader {
  size_t size_of_block;     // 8 bytes
  int free;                 // 4 bytes
                            // 4 bytes (padding)
  struct BlockHeader *next; // 8 bytes
  struct BlockHeader *prev; // 8 bytes
} header;                   // 32 bytes

void *my_malloc(size_t size_to_allocate);
void my_free(void *ptr);

/* Internal helpers */
header *find_free_block(size_t size);
void split_block(header *block, size_t size);
void insert_into_free(header *block);
void remove_from_free(header *block);
header *request_from_os(size_t size);
void coalescing(header *block);

static inline header *next_block(header *block);

static inline header *next_block(header *block) {
  return (header *)((char *)block + block->size_of_block + sizeof(header));
}

#endif
