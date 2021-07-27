#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "List.h"


//  Stack for storing number list .
typedef struct numnode
{
	number *a;
	struct numnode *p;
}numnode;

typedef numnode *numstack;

void ninit(numstack *s);

void npush(numstack *s, number *a);

number *npop(numstack *s);

int nisempty(numstack *s);



// Stack for storing character Operators.

typedef struct charnode
{
	char a;
	struct charnode *p;
}charnode;

typedef charnode *charstack;

void chinit(charstack *s);

void chpush(charstack *s, char t);

char chpop(charstack *s);

char chpeek(charstack s);

int chisempty(charstack *s);

#endif // STACK_H_INCLUDED
