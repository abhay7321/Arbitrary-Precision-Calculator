#include <stdlib.h>
#include "Stack.h"

// Stack implementation to store number list.
void ninit(numstack *s)
{
	*s = NULL;
}

void npush(numstack *s, number *t)
{
	numstack temp;
	temp = (numnode *)malloc(sizeof(numnode));
	temp->a = t;
	temp->p = *s;
	*s = temp;
}

number *npop(numstack *s)
{
	number *t;
	numstack temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->p;
	free(temp);
	return t;
}

int nisempty(numstack *s)
{
	return *s == NULL;
}

//  Stack implementation to store character Operators.
void chinit(charstack *s)
{
	*s = NULL;
}

void chpush(charstack *s, char t)
{
	charstack temp;
	temp = (charnode *)malloc(sizeof(charnode));
	temp->a = t;
	temp->p = (*s);
	*s = temp;
}

char chpop(charstack *s)
{
	char t;
	charstack temp;
	temp = (*s);
	t = (*s)->a;
	*s = (*s)->p;
	free(temp);
	return t;
}

char chpeek(charstack s)
{
	return s->a;
}

int chisempty(charstack *s)
{
	return *s == NULL;
}