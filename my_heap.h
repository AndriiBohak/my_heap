#ifndef MEMORY_HEAP
#define MEMORY_HEAP



//@brief function to create heap
//@param  size  size of your heap
//@return       pointer to begin of heap
void* createHeap(size_t sizeOfHeap);

//@brief allocate memory block
//@param  size size of memory block in bytes
//@return      pointer to allocated block or NULL
unsigned int myMalloc(size_t sizeOfMemory);


//@brief changes the size of the memory block pointed by ptr
//@param  pointer  pointer to memory block previously allocated
//@param  size     new size of memory block
unsigned int my_Realloc(unsigned int pointer, size_t size);

//@brief  deallocatr memory block
//@param  pointer  pointer to a memory block previously allocated with malloc
//@return          none
void myFree(unsigned int pointer);


//@brief  function to show memory map
//@return  none
void myShowMap();


#endif