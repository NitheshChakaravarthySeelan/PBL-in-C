#include "allocator.h"
#include <stddef.h>
#include <unistd.h>

// [Block_Header + The Actual Memory]
// After allocating the malloc should return the ptr to the Actual Memory
header *free_list_head = NULL;

void *my_malloc(size_t size) {
  header *free_block = find_free_block(size);

  // If false
  // Request actual memory from os
  // return
  // If true
  // Cut the size of the block. (In this process we will be taking only the
  // sliced part) Change the state of the free and change the pts in the free
  // memory.

  if (free_block) {
    split_block(free_block, size);
    free_block->free = 0;
    remove_from_free(free_block);
    return (void *)(free_block + 1);
  }

  free_block = request_from_os(size);
  if (!free_block) {
    return NULL;
  }
  return (void *)(free_block + 1);
}

void my_free(void *ptr) {
  if (!ptr) {
    return;
  }
  // From the ptr we need to take the header
  // Change it to free and insert into the free_list.
  // Coalescing forward only.

  header *block = (header *)ptr - 1;
  block->free = 1;

  insert_into_free(block);
  coalescing(block);
}

header *find_free_block(size_t size) {
  header *curr = free_list_head;

  while (curr) {
    if (curr->size_of_block >= size) {
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}

void split_block(header *block, size_t size) {
  if (block->size_of_block < size + sizeof(header)) {
    return;
  }

  // Doubt why block + 1
  // Explicit type casting.
  // I've heard somewhere casting to char used like somewhere in memory cause
  // its 1 byte.
  header *new_block = (header *)((char *)(block + 1) + size);

  new_block->size_of_block = block->size_of_block - (size + sizeof(header));
  new_block->free = 1;
  new_block->next = NULL;
  new_block->prev = NULL;

  block->size_of_block = size;
  insert_into_free(new_block);
}

// Inserting using LIFO.
void insert_into_free(header *block) {
  block->next = free_list_head;
  block->prev = NULL;

  if (free_list_head) {
    free_list_head->prev = block;
  }
  free_list_head = block;
}

void remove_from_free(header *block) {
  if (block->prev) {
    block->prev->next = block->next;
  } else {
    free_list_head = block->next;
  }

  if (block->next) {
    block->next->prev = block->prev;
  }

  block->next = NULL;
  block->prev = NULL;
}

header *request_from_os(size_t size) {
  // If we came here we don't have any free blocks.
  size_t total = sizeof(header) + size;

  header *block = sbrk(total);

  if (block == (void *)-1) {
    return NULL;
  }

  block->size_of_block = size;
  block->free = 0;
  block->next = NULL;
  block->prev = NULL;
  return block;
}

void coalescing(header *block) {
  header *next = next_block(block);

  if (!next || !next->free) {
    return;
  }

  remove_from_free(next);
  block->size_of_block += next->size_of_block + sizeof(header);
}


