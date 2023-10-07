# Malloc

A basic first-fit malloc implementation.

Signature: `void* malloc(size_t size);`

Resources used:
- https://wiki-prog.infoprepa.epita.fr/images/0/04/Malloc_tutorial.pdf 

Requirements:
* malloc will allocate a number of bytes
* malloc will return a pointer to the allocated space
* the space cannot be used until freed
* supports resize() and free()
* return NULL if malloc fails to allocate memory

### Memory layout of a process:

Each process has a virtual address space dynamically translated into physical address space by the MMU (and the kernel). 
The stack stores local and volatile data. The heap stores program data. The heap has a starting point and an endpoint called **break**. This break position makes the split between the mapped space of the virtual memory and an unmapped region of the heap.

To code malloc, we need to know where the heap begins and where the break position is.

- **brk** and **sbrk**:
    - `int brk(const void *adr);` => places the break at a given address and returns 0 on success, else -1
    - `void* sbrk(intptr_t incr);` => moves the break by the given increment (in bytes). Depending on system implementation, it returns the previous or the new break adress. On failure, it returns (void *)-1 and set
errno. When the increment is 0, the return value = the current break.

- **mmap()**
    - A syscall used to directly map files in the memory. It can allocate a specific amount of memory and **munmap** can deallocate it.








