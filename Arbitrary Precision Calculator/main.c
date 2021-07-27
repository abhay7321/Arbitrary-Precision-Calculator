#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "Stack.h"
#include "Functions.h"
#include <limits.h>
#define OPERAND	100
#define OPERATOR 200
#define END	300

typedef struct token
{
	int type;
	number *num;
	char op;
}token;


number* evaluate(number* nos1 , number* nos2 , char op)
{
    if(op=='+')
    {
        number *result=add(nos1 ,nos2);
        return result;
    }
    else if(op=='-')
    {
        number *result=sub(nos1 ,nos2);
        return result;
    }
    else if(op=='*')
    {
        number *result=mult(nos1 ,nos2);
        return result;
    }
    else if(op=='/')
    {
        number *result=division(nos1 ,nos2);
        return result;
    }
    else if(op=='%')
    {
        number *result=modulus(nos1, nos2);
        return result;
    }

    return NULL;

}





int Precedence(char ope)
{
    if((ope=='+')||(ope=='-'))
        return 1;
    else if((ope=='*')||(ope=='/')||(ope=='%'))
        return 2;
    else
        return 3;
}



int Associvity(char ope)
{
    if(ope=='^')
        return 1;   //Associvity is from right to left.
    else            //Associvity is from left to right.(+, -, *, /)
        return 0;
}




int isDigit(char c)
{
	int m=0;
	if (c>='0' && c<='9')
	{
		m=1;
	}
	return m;
}




int isoperator(char c)
{
	int m=0;

	if( (c=='+') || (c=='-') || (c=='*') || (c=='/') || (c=='%') || (c=='^') )
	{
		m=1;
	}

	return m;
}


token gettoken(char *expr ,int *reset)
{
	static int i = 0;

	if(*reset==1)
	{
	    *reset=0;
	    i=0;
	}


	number *a = (number *)malloc(sizeof(number));
	initNumber(a);

	char c=expr[i];
    token t;
	int decipt=0;


	while(1)
	{
		if (c=='(' || c==')')
		{
			i++;

			while(expr[i]==' ')
			{
				i++;
			}
			t.op=c;
			t.type=OPERATOR;
			return t;
		}
		else if (isDigit(c) || expr[i]=='.')
		{
			addDigit(a, c);
			int j=i+1;
			while (isDigit(expr[j]) || expr[j]=='.')
			{
				if (expr[j]=='.')
				{
					decipt=1;
				}
				else
				{
					addDigit(a, expr[j]);
					if (decipt==1)
					{
						a->dec++;
					}
				}
				j++;
			}
			i=j;
			while (expr[i]==' ')
			{
				i++;
			}
			t.type=OPERAND;
			t.num=a;
			return t;
		}
		else if (isoperator(c))
		{
			t.type=OPERATOR;
			t.op=c;
			i++;
			while (expr[i]==' ')
			{
				i++;
			}
			return t;
		}
		else if (c=='\0')
		{
			t.type=END;
			return t;
		}
	}
}















number *infix_eval(char *exp)
{
    numstack num_st;
	charstack char_st;
	ninit(&num_st);
	chinit(&char_st);

    int reset=1;

	token t,prev;
	prev.type=1;
	prev.op='#';

	while(1)
	{
		t = gettoken(exp ,&reset);
        if (t.type==prev.type ){
            if (  t.op!='(' && t.op!=')'  && prev.op!='(' && prev.op!=')' ){
                return NULL;
            }
        }
        prev.type=t.type;
        prev.op=t.op;
		if(t.type == OPERAND)
		{
			npush(&num_st, t.num);
		}
		else if(t.type == OPERATOR)
        {
            if(t.op=='(')//push operator token on character stack
            {
                chpush(&char_st ,t.op);
            }
            else if(t.op==')')
            {
                while(chpeek(char_st)!='(')
                {
                    char currchar=chpop(&char_st); //currchar in this operator is stored
                    number *a,*b;
                    a=npop(&num_st);
                    b=npop(&num_st);

                    number *result=evaluate(b ,a ,currchar);
                    npush(&num_st,result);

                }
                //char popped=cpop(&cs);        // for popping the ( opening bracket
                chpop(&char_st);
            }
            else
            {
                if((chisempty(&char_st))||(chpeek(char_st)=='('))
                {
                    chpush(&char_st ,t.op);
                }
                else
                {
                    int in_precedence=Precedence(t.op);
                    int top_precedence=Precedence(chpeek(char_st));
                    int pushed=0;

                    if(top_precedence > in_precedence)
                    {
                        while(top_precedence > in_precedence)
                        {
                            char curr_char=chpop(&char_st);
                            number *a,*b;
                            a=npop(&num_st);
                            b=npop(&num_st);

                            number *result=evaluate(b ,a ,curr_char);
                            npush(&num_st,result);


                            if((chisempty(&char_st))||(chpeek(char_st)=='('))
                            {
                                pushed=1;
                                chpush(&char_st ,t.op);
                                break;
                            }

                            top_precedence=Precedence(chpeek(char_st));

                        }
                        if(pushed==1)
                            continue;
                    }

                    if(top_precedence == in_precedence)
                    {
                        int asso=Associvity(t.op);

                        if(asso==1)
                        {
                            chpush(&char_st ,t.op);
                        }
                        else
                        {
                            int ispushed=0;

                            while(top_precedence == in_precedence)
                            {
                                char popped=chpop(&char_st);

                                number *a,*b;
                                a=npop(&num_st);
                                b=npop(&num_st);

                                number *result=evaluate(b ,a ,popped);
                                npush(&num_st,result);


                                if((chisempty(&char_st))||(chpeek(char_st)=='('))
                                {
                                    chpush(&char_st ,t.op);
                                    ispushed=1;
                                    break;
                                }

                                top_precedence=Precedence(chpeek(char_st));
                            }
                            if(ispushed==0)
                            {
                                chpush(&char_st ,t.op);
                            }
                            continue;
                        }
                    }

                    if(in_precedence > top_precedence)
                    {
                        chpush(&char_st ,t.op);
                        continue;
                    }
                }
            }

        }
        else if(t.type==END)
        {
            break;
        }
    }

    while(!chisempty(&char_st))
    {
        char currchar=chpop(&char_st); //currchar in this operator is stored
        number *a,*b;
        a=npop(&num_st);
        b=npop(&num_st);

        number *result=evaluate(b ,a ,currchar);
        npush(&num_st,result);
    }

    return npop(&num_st);
}













//Taking expression in a character array
//We read the expression character by character and store it in the line character array
//Here we have taken the max size of the expression to be 2048
int read(char *line, int len)
{
	int i, opening_brac=0, closing_brac=0, mask=0, flag=0;
	char ch;
	i = 0;
	while(i < len - 1)
	{
		ch = getchar();
		if (ch=='('){
            opening_brac++;
        }
        else if(ch==')'){
            closing_brac++;
        }
        if (closing_brac>opening_brac){
            flag=1;
            break;
        }
		if(ch == '\n')
		{
			line[i++] = '\0';
			mask=1;
			break;
			//return i - 1;
		}
		else
			line[i++] = ch;
	}
    if ((flag==1) || (opening_brac!=closing_brac)){
        printf("Invalid Expression! Please check for Brackets.\n");
        return 0;
    }
    if (mask==1){
        return i-1;
    }
	line[len - 1] = '\0';
	return len - 1;
}











int main()
{
	number *r;
	char expr[3000];
	while(read(expr, 3000))
	{

        //Whenever '(' bracket occurs and after it nos written as +3534....or -2525235....
        //then we write it as 0 + 3534.... or 0 + 2525235...


		int i;
        for(i = 0; i < strlen(expr); i++)
        {
            if(expr[i] == '(')
            {
                int j = 1;
                while(1)
                {
                    if(expr[i + j] == ' ')
                    {
                        j++;
                    }
                    else
                    {
                        break;
                    }
                }
                if((expr[i + j] == '-') || (expr[i + j] == '+'))
                {
                    int temp = strlen(expr);
                    while(temp >= i + j)
                    {
                        expr[temp + 1] = expr[temp];
                        temp--;
                    }
                    expr[i + j] = '0';
                }
            }
        }



		r = infix_eval(expr);
		if(r != NULL)
			printNumber(*r);
		else
			printf("Invalid  Expression\n");
	}
	return 0;
}
