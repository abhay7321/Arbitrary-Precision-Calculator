#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#define PLUS 1
#define MINUS -1



typedef struct digit
{
	int num;
	struct digit *next, *prev;
}digit;



typedef struct number
{
	int sign, dec;
	digit *head, *tail;
}number;



void initNumber(number *num);					//To initialize the number
void addDigit(number *num, char c);			//Append digit at end of number
void printNumber(number num);					//To print the entire number (all digits)
void appendleft(number *num, int n);			//Append at start
int length(number num);						//To find the length of number
void remov(number *num, int pos);				//To remove a digit at an index p inside linked list
void zeroRemov(number *num);					//To remove extra zeros on extreme left and on extreme right



#endif // LIST_H_INCLUDED
