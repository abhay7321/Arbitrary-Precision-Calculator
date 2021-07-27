#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "List.h"
#include "Functions.h"

//Function to equal the digits after decimal point , adding zeros on right side .
void make_decimal_equal(number *a, number *b)
{
	int i;
	if(a->dec > b->dec)
	{
		int diff = a->dec - b->dec;
		for(i = 0; i < diff; i++)
		{
			addDigit(b, '0');
			b->dec++;
		}
	}
	else if(b->dec > a->dec)
	{
		int diff = b->dec - a->dec;
		for(i = 0; i < diff; i++) {
			addDigit(a, '0');
			a->dec++;
		}
	}
}

//equals the length of both numbers by prepending zeros to small number on left side
void lengthEqual(number *a, number *b)
{
	int gap;
	gap = length(*a) - length(*b);
	if(gap > 0)
	{
		int i = 0;
		while(i < gap)
		{
			appendleft(b, 0);
			i++;
		}
	}
	else if(gap < 0)
	{
		int i = 0;
		gap = -gap;
		while(i < gap)
		{
			appendleft(a, 0);
			i++;
		}
	}
}

//checks whether the number is zero or not , returns 0 if it is zero number.
int zeroNumber(number a)
{
	int i, flag = 0;
	digit *p = a.head;
	for(i = 0; i < length(a); i++)
	{
		if(p->num != 0)
			flag = 1;
		 p = p->next;
	}
	return flag;
}


//Addition Operation
number *add(number *a, number *b)
{
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	make_decimal_equal(a, b);		//to equal nos of digits in a,b after decimal pt i.e. on RHS
	if(a->sign != b->sign)
	{
		if(a->sign == MINUS)
		{
			a->sign = PLUS;
			ans = sub(b, a);
		}
		else if(b->sign == MINUS)
		{
			b->sign = PLUS;
			ans = sub(a, b);
		}
	}
	else if(a->sign == b->sign)
	{
		int i, n1, n2, carry = 0, sum;
		int len_a, len_b;
		digit *t1 = a->tail;
		digit *t2 = b->tail;
		len_a = length(*a);
		len_b = length(*b);
		if(a->sign == MINUS)
			ans->sign = MINUS;
		else
			ans->sign = PLUS;
		if(len_a >= len_b)
		{
			for(i = 1; i <= len_b; i++)
			{
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_a - len_b; i++)
			{
				n1 = t1->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t1 = t1->prev;
			}
		}else
		{
			for(i = 1; i <= len_a; i++)
			{
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_b - len_a; i++) {
				n1 = t2->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t2 = t2->prev;
			}
		}
		ans->dec = a->dec;    //Because of decimalequal() a and b have same decimals
		if(carry != 0)
			appendleft(ans, carry);
	}
	return ans;
}

/*
Function for finding bigger number among given nos .
First we make them equal length numbers , by making ther sizes before decimal equal and afer decimal also equal. */
int compare(number a, number b)
{
    make_decimal_equal(&a, &b);      //Function to equal the digits after decimal point , adding zeros on right side .
	lengthEqual(&a, &b);	//equals the length of both numbers by prepending zeros to small number on left side .

	digit *p, *q;
	int len;
	int i;
	len = length(a);
	p = a.head;
	q = b.head;
	for(i = 1; i <= len; i++)
	{
		if(p->num > q->num)
			return 1;  //i.e. number a greater than number b.
		else if(p->num < q->num)
			return -1;  //i.e. a is less than b.
		p = p->next;
		q = q->next;
	}
	return 0;    //i.e. both numbers are equal.
}


//Substraction operation.
number *sub(number *a, number *b)
{
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);

	//decimal digits and length made equal.
	make_decimal_equal(a, b);
	lengthEqual(a, b);

	if(a->sign != b->sign)
	{
		if(a->sign == MINUS)
		{
			a->sign = PLUS;
			ans = add(a, b);
			ans->sign = MINUS;
		}
		else if(b->sign == MINUS)
		{
			b->sign = PLUS;
			ans = add(a, b);
			ans->sign = PLUS;
		}
	}
	else if(a->sign == b->sign)
	{
		if(a->sign == MINUS)
		{
			a->sign = b->sign = PLUS;
			ans = sub(b, a);
		}
		else if(a->sign == PLUS)
		{
			int n1, n2, diff, borrow = 0, i, len;
			digit *t1 = a->tail;
			digit *t2 = b->tail;
			//length of both numbers is same now because of lengthEqual.
			len = length(*b);
			if(compare(*a, *b) == 1)
			{
				for(i = 1; i <= len; i++)
				{
					n1 = t1->num;
					n2 = t2->num;
					n1 = n1 - borrow;
					if(n1 >= n2)
					{
						diff = n1 - n2;
						borrow = 0;
						appendleft(ans, diff);
					}
					else {
						n1 = n1 + 10;
						diff = n1 - n2;
						borrow = 1;
						appendleft(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else if(compare(*a, *b) == -1)
			{
				ans->sign = MINUS;
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n2 = n2 - borrow;
					if(n2 >= n1) {
						diff = n2 - n1;
						borrow = 0;
						appendleft(ans, diff);
					}
					else {
						n2 = n2 + 10;
						diff = n2 - n1;
						borrow = 1;
						appendleft(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else
			{
				if(compare(*a, *b) == 0)
				{
					appendleft(ans, 0);
				}
			}
		}
	}
	ans->dec = a->dec;
	return ans;
}





//Multiplication Operation.
number *mult(number *a, number *b)
{
	number *ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	//checks if any one of the numbers is zero.
	if((zeroNumber(*a) == 0) || (zeroNumber(*b) == 0))
	{
		addDigit(ans, '0');
		return ans;
	}





    digit *t1, *t2;
    int len_b = length(*b);

    t2=b->tail;

    for(int i=0 ; i<len_b ; i++)
    {
        t1=a->tail;
        int carry=0;

        number *temp = (number *)malloc(sizeof(number));
        initNumber(temp);

        while(t1!=NULL)
        {
            int nos;
            nos = t1->num*t2->num + carry ;

            carry=nos/10;
            nos=nos%10;
            appendleft(temp ,nos);
            t1=t1->prev;
        }
        if (carry){
            appendleft(temp ,carry);
        }
        t2=t2->prev;

        for(int j=0 ;j<i ;j++)
        {
            addDigit(temp ,'0');
        }

        ans=add(ans , temp);
        free(temp);
    }

    //assigning sign to answer
	if(a->sign == b->sign)
	{
		ans->sign = PLUS;
		a->sign = b->sign = PLUS;
	}
	else
	{
		ans->sign = MINUS;
		a->sign = b->sign = PLUS;
	}


    ans->dec = a->dec + b->dec;
    return ans;

}




//Division Operation.
number *division(number *m, number *n)
{
	//Handling Zero division error
	if(zeroNumber(*n) == 0)
	{
		printf("Dividing by Zero is not allowed.\n");
		return NULL;
	}

	//Removing zeros from left and right extremes
	zeroRemov(m);
	zeroRemov(n);

	int k = m->dec > n->dec ? m->dec : n->dec;
	int i = 0;

	while(i < k)
	{
		if(m->dec > 0)
			m->dec--;
		else
			addDigit(m, '0');


		if(n->dec > 0)
			n->dec--;
		else
			addDigit(n, '0');
		i++;
	}

	i = 9;

	number *c, *d, *ans, *q, *pro;
	c = (number *)malloc(sizeof(number));		//number to store i 	,		appendleft(c, i);
	d = (number *)malloc(sizeof(number));		//number after sbtraction =>diff
	ans = (number *)malloc(sizeof(number));		//ans = sub(d, pro);
	pro = (number *)malloc(sizeof(number));		//divisor*i		,		pro = mult(n, c);
	q = (number *)malloc(sizeof(number));		//quotient

	initNumber(ans);
	initNumber(c);
	initNumber(q);
	initNumber(d);


	//Initialising sign for ans
	if(m->sign == n->sign)
	{
		q->sign = PLUS;
		m->sign = n->sign = PLUS;
	}
	else
	{
		q->sign = MINUS;
		m->sign = n->sign = PLUS;
	}

	//m/n

	digit *p = m->head;
	char ch = p->num + '0';
	addDigit(d, ch);
	while(q->dec < SCALE)
	{
		while(i >= 0)
		{
			appendleft(c, i);           //here we are trying to find the number which is greater
			pro = mult(n, c);           //or equal to number n and calculating the difference between that number and n
			ans = sub(d, pro);

			if(ans->sign != MINUS) {
				addDigit(q, i + '0');
				digit *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				break;
			}
			else
			{
				digit *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				i--;
			}

		}
		d = ans;
		if(p->next != NULL)
		{
			p = p->next;
			ch = p->num + '0';
			addDigit(d, ch);
		}
		else
		{
			q->dec++;
			addDigit(d, '0');
		}
		i = 9;
		digit *tmp = c->head;
		free(tmp);
		c->head = c->tail = NULL;
	}
	q->dec--;
	return q;
}




//FORMULA :- remainder = a - floor_division(a/b) * b
number *modulus(number *a, number *b) {
	if(zeroNumber(*b) == 0) {
		printf("ERROR : Modulo by Zero is not allowed.\n");
		return NULL;
	}
	int tempsign;
	if(a->sign == MINUS) {
		tempsign = MINUS;
		a->sign = b->sign = PLUS;
	}
	else {
		tempsign = PLUS;
		a->sign = b->sign = PLUS;
	}
	make_decimal_equal(a, b);
	int a_dec = a->dec;
	number *ans = (number *)malloc(sizeof(number));
	number *temp = (number *)malloc(sizeof(number));
	initNumber(ans);
	initNumber(temp);
	temp = division(a, b);
	if(temp->dec != 0) {
		int pos = length(*temp) - 1;
		while(temp->dec != 0) {
			remov(temp, pos);
			temp->dec--;
			pos--;
		}
	}
	temp = mult(temp, b);
	ans = sub(a, temp);
	ans->sign = tempsign;
	ans->dec = a_dec;
	return ans;
}


