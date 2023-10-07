#include<iostream>
#include<cstdlib>

int main() {

    // Malloc allocating 1 int memory block
    int* p1 = (int*)malloc(sizeof(int));
    
    // Assign a value to the allocated memory
    *p1 = 1;

    std::cout << *p1 << '\n';
    
    // Assign 10 int memory blocks
    int* p10 = (int*)malloc(sizeof(int));

    if (!p10) {
        std::cout<< "Memory Allocation Failed" << '\n';
    }
    
    // Set some values
    for (int i = 0; i < 10; i ++) {
        p10[i] = i*2;
    }

    std::cout << "Printed values: " << '\n';

    for (int i = 0; i < 10; i ++) {
        std::cout << *(p10 + i) << '\n';
        //std::cout << p10[i] << '\n';
    }
    
    free(p1);
    free(p10);
    return 0;
}