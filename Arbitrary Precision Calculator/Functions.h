#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define SCALE 20

int compare(number a, number b);
void make_decimal_equal(number *a, number *b);        //To make nos of digits after point , equal .
number *add(number *a, number *b);              //If both of same sign use addition else call the subtraction function .
number *sub(number *a, number *b);
number *mult(number *a, number *b);
number *division(number *a, number *b);
number *modulus(number *a, number *b);


#endif // FUNCTIONS_H_INCLUDED