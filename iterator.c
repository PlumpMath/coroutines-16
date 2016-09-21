#include "iterator.h"
#include "thunk.h"
#include <stdlib.h>
#include <stdio.h>

#define STACK_LONGS 1024

extern void doSomething(long *p, long **pp);

struct Iterator {
    long stack[1024];
    //to keep track and see if we are in yield deadlock
    int deadlock;
    //holds the location of the iterator
    long* location;
    //which function this iterator is for
    F0 func;

};

//globals to keep track of Iterator we are currently on and which iterator is being used
static Iterator* currentIter=0;
static Iterator* callingIter=0;
static long constant=0;


static void deadlock(void) {
    printf("deadlock\n");
    exit(0);
}

//function to handle nexts and return the return value when no yield present
static void returnYield(void)
{
    //get the return value of the function
    long returnValue=currentIter->func();
    while(1)
      yield(returnValue);
}


Iterator* newIterator(F0 func) {
  //initiate iterator
  Iterator* iter=(Iterator *)malloc(sizeof(*iter));
  iter->deadlock=0;
  iter->func=func;
  //set locations in stack so we pop to correct places
  iter->stack[STACK_LONGS-200-1]=(long)returnYield;
  iter->location=&iter->stack[STACK_LONGS-200-7];
  return iter;

}
long next(Iterator* p) {
  //store the last iterator that was called
  Iterator* prev=callingIter;
  //if we are in main function
  if(currentIter==0)
    currentIter=newIterator(0);
  //set current iter deadlock to 1
  currentIter->deadlock=1;
  if(p->deadlock==1)
    deadlock();
  //set calling iter to current.
  callingIter=currentIter;
  //current iter becomes p (passed in to next)
  currentIter=p;
  //swap stacks
  doSomething(p->location, &callingIter->location);
  //switch iterators back
  currentIter=callingIter;
  callingIter=prev;
  //take away deadlock
  currentIter->deadlock=0;
  return constant;
}


void yield(long v)
{
    //grab the long
    constant=v;
    //swap stacks
    doSomething(callingIter->location,&currentIter->location);
}
