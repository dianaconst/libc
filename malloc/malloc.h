#ifndef MALLOC_H
#define MALLOC_H

#include <sys/types.h>
#include <unistd.h>

#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#define BLOCK_SIZE 40
#define align8bytes(x) (((x) + 7) & (-8))
#else
#define ENVIRONMENT32
#define BLOCK_SIZE 20
#define align4bytes(x) (((((x)-1)>>2)<< 2)+4)
#endif
#endif

// A block containing the size, a pointer to the next block and a flag to check if the block is free to use
struct s_block {
    size_t size;
    t_block next;
    t_block prev;
    int free;
    void* ptr;

    // A pointer to the deallocated block
    char data[1];
};

typedef struct s_block* t_block;

t_block find_block(t_block* last, size_t size);
t_block extend_heap(t_block last, size_t size);
void split_block(t_block b, size_t size);
t_block fusion(t_block b);
t_block get_block(void* p);
int valid_addr(void* p);
void free(void* p);
void* malloc(size_t size);

#endif
