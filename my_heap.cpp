#include "my_heap.h"

#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

struct 
{
  void *  firthBlokOfMemory;
  size_t  syzeOfHeap;
  bool    isStored;
  unsigned int    isFreeBlokcs; 
} static myHeap;

struct blockOfMemory
{
  unsigned int address;
  bool isFree;
  size_t size;
};

static struct
{
  unsigned maxcountOfBlocks;
  unsigned countOfBlocks;
  size_t sizeOfBlocks;
  blockOfMemory* blocks;
} my_blocks;



void* createHeap(size_t sizeOfHeap)
{
  if(sizeOfHeap<=0)
  {
    return NULL;
  }
  myHeap.isFreeBlokcs=0;
  myHeap.firthBlokOfMemory = calloc(sizeOfHeap,sizeof(myHeap.firthBlokOfMemory));
  memset(myHeap.firthBlokOfMemory,0,sizeOfHeap);
  if(myHeap.firthBlokOfMemory!=NULL){

      my_blocks.blocks = (blockOfMemory*)(malloc(sizeof(blockOfMemory)*sizeOfHeap));

    if(my_blocks.blocks!=NULL)
    {
      myHeap.isStored   = true;
      myHeap.syzeOfHeap = sizeOfHeap;
      my_blocks.maxcountOfBlocks = sizeOfHeap;
      my_blocks.countOfBlocks = 0;
      my_blocks.sizeOfBlocks = 0;
    }

    return myHeap.firthBlokOfMemory;
  }	else
    return NULL;

}



unsigned int myMalloc(size_t sizeOfMemory)
{
  if (myHeap.isStored)
  {
    if(my_blocks.countOfBlocks==0)
    {
      my_blocks.blocks[my_blocks.countOfBlocks].address=0;
      my_blocks.blocks[my_blocks.countOfBlocks].isFree=false;
      my_blocks.blocks[my_blocks.countOfBlocks].size=sizeOfMemory;
      my_blocks.countOfBlocks++;
      my_blocks.sizeOfBlocks+= sizeOfMemory;
      return my_blocks.blocks[0].address;	

    }
    else
    {
      if(myHeap.isFreeBlokcs>=1){
        for (unsigned int i = 0; i < my_blocks.countOfBlocks; i++)
        {
          if(my_blocks.blocks[i].isFree==true && my_blocks.blocks[i].size==sizeOfMemory)
          {
            my_blocks.blocks[i].isFree =false;
            myHeap.isFreeBlokcs-=1;
            return my_blocks.blocks[i].address;

          }				
          /*else if(my_blocks.blocks[i].isFree==true && my_blocks.blocks[i].size>sizeOfMemory)
          {



          }*/
        }
      }
      if(my_blocks.maxcountOfBlocks-my_blocks.countOfBlocks<sizeOfMemory){
        std::cout<<"HEAP IS FULL";
        exit(-1);
      }
      my_blocks.blocks[my_blocks.countOfBlocks].isFree=false;
      my_blocks.blocks[my_blocks.countOfBlocks].address= my_blocks.blocks[my_blocks.countOfBlocks-1].address+
                                                          my_blocks.blocks[my_blocks.countOfBlocks-1].size;
      my_blocks.blocks[my_blocks.countOfBlocks].size=sizeOfMemory;

      my_blocks.sizeOfBlocks+=sizeOfMemory;
      my_blocks.countOfBlocks+=1;
      return my_blocks.blocks[my_blocks.countOfBlocks-1].address;


    }
  }
}



void myFree(unsigned int pointer){
  for (unsigned int i = 0; i < my_blocks.countOfBlocks; i++)
  {
    if(my_blocks.blocks[i].address==pointer){
      my_blocks.blocks[i].isFree= true;
      myHeap.isFreeBlokcs+=1;
      return;
    }
  }
}



void myShowMap()
{
  unsigned int freeMemory=0;
  std::cout<<std::setw(30)<<"Map of Heap\n"<<std::endl;

  std::cout<<std::setw(7)<<"Adress"<<std::setw(13)<<"Real Adress"<<std::setw(9)
    <<"Size"<<std::setw(9)<<"EmpRy"<<std::setw(12)<<"DATA"<<std::endl;

  for (unsigned int  i = 0; i < my_blocks.countOfBlocks; i++) {
    std::cout << std::endl << std::setw(5) << std::dec <<my_blocks.blocks[i].address 
      << std::setw(10) << std::hex << (unsigned int)myHeap.firthBlokOfMemory + my_blocks.blocks[i].address 
      << std::setw(10) << std::dec << my_blocks.blocks[i].size
      << std::setw(10) <<  my_blocks.blocks[i].isFree;
    if (my_blocks.blocks[i].isFree==true) 
      freeMemory += my_blocks.blocks[i].size;
    std::cout << std::setw(6);

    for(unsigned int j=0; j<my_blocks.blocks[i].size;j++){
      unsigned char* data= (unsigned char*)(myHeap.firthBlokOfMemory)+my_blocks.blocks[i].address+j;
      std::cout << std::hex <<(unsigned int)(*data);   
    }
  }

  std::cout << std::endl  << "\nAmount of blocks:" << std::setw(8) << std::dec
    << my_blocks.countOfBlocks << "\nSize of blocks: " << std::setw(9) 
    << my_blocks.sizeOfBlocks  << "\nMax syze of Blocks: " << std::setw(5) 
    << my_blocks.maxcountOfBlocks  << "\nMax Emount of Blocks: " << std::setw(3) 
    << my_blocks.maxcountOfBlocks - my_blocks.sizeOfBlocks
    << "\nFree Memory:    " << std::setw(9) 
    << freeMemory << std::endl;
}



unsigned int my_Realloc(unsigned int pointer, size_t size)
{

  blockOfMemory* copy = NULL;
  blockOfMemory* copy2 = NULL;
  bool isLast =false;
  if(myHeap.isStored)
  {

    for (unsigned int i = 0; i < my_blocks.countOfBlocks; i++)
    {
      bool checkPointer = my_blocks.blocks[i].address  == pointer;
      bool checkSize    = my_blocks.blocks[i].size    == size;
      bool checkEmpty   = my_blocks.blocks[i].isFree  == true;
      if(checkPointer==true)
      {
        if (checkSize == false)
        {
          copy=&my_blocks.blocks[i];

          if (i == my_blocks.countOfBlocks-1)
            isLast=true;
        }else {
          return my_blocks.blocks[i].address;
        }
      }if(checkSize&&checkEmpty){
      copy=&my_blocks.blocks[i];
      }
      }
      if(isLast==true)
      {
        if(my_blocks.sizeOfBlocks+size<=myHeap.syzeOfHeap)
        {
          my_blocks.sizeOfBlocks-= copy->size;
          copy->size=size;
          my_blocks.sizeOfBlocks+=copy->size;
        }else{
          std::cout << "HEAP IS FULL";
          exit(-1);
        }

      }

      if(copy2!=NULL){
        my_blocks.sizeOfBlocks-=copy->size;
        copy->isFree=true;
        copy2->isFree= false;
        char * firthAddress=(char*)myHeap.firthBlokOfMemory+copy->address;   
        char * secondAddress=(char*)myHeap.firthBlokOfMemory+copy2->address;  
        for (unsigned int i = 0; i < copy->size; i++)
        {
          *(secondAddress)=*(firthAddress);
          firthAddress++;
          secondAddress++;
        }
        return copy->address;
      }
      if (size+my_blocks.sizeOfBlocks>my_blocks.maxcountOfBlocks)
      {
        std::cout << "HEAP IS FULL";
        exit(-1);
      }else
      {
        my_blocks.blocks[my_blocks.countOfBlocks].address=my_blocks.blocks[my_blocks.countOfBlocks-1].address
          +my_blocks.blocks[my_blocks.countOfBlocks-1].size;
        my_blocks.blocks[my_blocks.countOfBlocks].size=size;
        my_blocks.blocks[my_blocks.countOfBlocks].isFree=false;
        my_blocks.sizeOfBlocks=my_blocks.sizeOfBlocks+size;

        char* firthAddress = (char*)myHeap.firthBlokOfMemory + copy->address;
        char* secondAddress = (char*)myHeap.firthBlokOfMemory + my_blocks.blocks[my_blocks.countOfBlocks].address;

        for (unsigned int i = 0; i < copy->size; i++)
        {
          *(secondAddress)=*(firthAddress);
          firthAddress++;
          secondAddress++;
        }
        my_blocks.countOfBlocks++;
        myFree(copy->address);
        return my_blocks.blocks[my_blocks.countOfBlocks-1].address;
      }
    }
    return pointer;
  }

 



