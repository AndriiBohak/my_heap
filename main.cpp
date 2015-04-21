#include"my_heap.h"



int main()
{

createHeap(20);
char* p=(char*)myMalloc(sizeof(char));
int* d=(int*)myMalloc(sizeof(int));
short* f=(short*)myMalloc(sizeof(short));
myShowMap();
myFree((unsigned int)f);

d = (int*)my_Realloc((unsigned int)d,2);
char* k=(char*)myMalloc(sizeof(char));
int* n=(int*)myMalloc(sizeof(int));
myShowMap();

return 0;


}