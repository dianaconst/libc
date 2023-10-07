#include "malloc.h"

// The base must be defined somewhere
void* base = NULL;

t_block find_block(t_block* last, size_t size) {
    t_block b = base;

    // We keep searching until we find a block that is okay to use
    while (b && !(b->free == 1 && b->size >= size)) {
        // Last will point to the last visited chunk in the end
        *last = b;
        b = b->next;
    }

    return (b);
}

t_block extend_heap(t_block last, size_t size) {
    t_block b;

    // We get the beginning of the current break
    b = sbrk(0);

    if (sbrk(BLOCK_SIZE + size) == (void*)-1)
        // failed
        return NULL;
    
    // Update the new block with the values 
    b->size = size;
    b->next = NULL;
    if (last)
        last->next = b;
    b->free = 0;

    return (b);
}

void split_block(t_block b, size_t s) {
    t_block new;
    new = b->data + s;
    new->next = b->next;
    new->free = 1;
    b->size = s;
    b->next = new;
}

t_block fusion(t_block b) {
    if (b->next && b->next->free) {
        b->size += BLOCK_SIZE + b->next->size;
        b->next = b->next->next;
        
        if (b->next)
            b->next->prev = b;
    }
    return (b);
}

t_block get_block(void *p) {
    char *tmp;
    tmp = p;
    
    tmp -= BLOCK_SIZE;
    p = tmp;
    return (p);
}

int valid_addr(void* p) {
    if (base) {
        if (p > base && p < sbrk(0)) {
            return (p == (get_block(p))->ptr);
        }
    }
    return (0);
}

void free(void* p) {
    t_block b;

    if (valid_addr(p)) {
        b = get_block(p);
        b->free = 1;

        // Fusion with prev
        if (b->prev && b->prev->free) 
            b = fusion(b->prev);
        
        if (b->next)
            fusion(b);
        else {
            if (b->prev)
                b->prev->next = NULL;
            else 
                base = NULL;
            brk(b);
        }
    }
}

void* malloc(size_t size) {
    t_block b, last;
    size_t s;
    s = align4bytes(size);

    if (base) {
        // Finds block
        last = base;
        b = find_block(&last, s);

        // It has found a valid block
        if (b) {
            // The remained size is bigger than half of the block and we can split
            if ((b->size - s) >= (BLOCK_SIZE + 4))
                split_block(b, s);
            b->free = 0;
        } 
        else {
            // No fitting block, extend the heap
            b = extend_heap(last, s);
            if (!b) 
                return(NULL);
        }
    }
    else {
        // If base is null, it means it's the first time we allocate memory 
        b = extend_heap(NULL, s);
        if (!b)
            return(NULL);
        base = b;
    }
    return (b->data);
}

void* calloc(size_t number, size_t size) {

}







