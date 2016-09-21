#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "thunk.h"

struct Iterator;
typedef struct Iterator Iterator;

/* Create a new iterator that runs the given function */
extern Iterator* newIterator(F0 func);

/* Run the iterator until it yields a value, returns that value */
extern long next(Iterator* iter);

/* Called by an iterator to yield a new value */
extern void yield(long value);

#endif
