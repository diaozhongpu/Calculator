/*
 * File:normal.c the code for a normal cauculator.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"normal.h"


void Normal()
{
	int i=0;
	double inputnum, result, a, b;
	double *ptinputnum=&inputnum, *ptresult=&result, *pta=&a, *ptb=&b;
			/*
			 *  pointer to store input number or number in storage
			 */
	char inputchar, curchar;
	char *ptinputchar=&inputchar,*ptcurchar=&curchar;
			/*
			 * pointer to the input character
			 */
	int ifnum=0,ifpoint=0,ifinput=1;
			/* ifnum: 0=last input is not number, 1= last input is a number,
			 * which indicate that if this time the input is also a number, it
			 * should be merged into the previous one.
			 * ifpoint: when the program is reading in a number,  0=it does not
			 * come across the fractional part, and 1 vice versa
			 * ifinput: 1=there still input to be read, be set to 0 when a '\n'
			 * is read in.
			 */
	Stack Number, Character;
			/*
			 * The Stack used to tempararily store input Number and Character
			 * before all of them is passed to the Output List.
			 */
	List Output;
			/*
			 * The List used to store output reverse Polish expression.
			 */
	Character=NewStack();
	Output=NewList();
			/*
			 * Initialize the Stack and List.
			 */
		
	getchar();
			/*
			 * Omit the excess '\n' in the input stream.
			 */
	printf("Please input:");
	while(ifinput)
			/*
			 * Tthe code will be executed if there are still input.
			 */
	{
		ptinputchar=(char*)malloc(sizeof(char)); 
		scanf("%c",ptinputchar);
		switch(*ptinputchar)
		{
			case '+': case '-':
			/*
			 * Execute when '+' or '-' is taken in
			 * When no previous operator is stored in Character Stack,
			 * it will pop two numbers in the Number Stack, and store them in
			 * the output correspondingly. Meaning the '+'/'-' operator will 
			 * act on them. 
			 * Otherwise, the operator with higher precedence will be precess
			 * first.
			 */
				if(IsEmpty(Character))
				{
					printf("[if]");
					Push(Character,ptinputchar,1);
				}
				else
				{
					printf("[else]");
					while(!IsEmpty(Character))
					{
						ptcurchar=Pop(Character);
						if(*ptcurchar=='(')
						{
							Push(Character,ptcurchar,1);
							break;
						}
						else
						{
							Add(Output,ptcurchar,1);
						}
					}
					Push(Character,ptinputchar,1);
				}
				printf("[+]");
				ifnum=0;
				ifpoint=0;
				break;
			case '*': case '/': 
			/*
			 * Execute when '*' or '/' is taken in.
			 * Similiar to case '+' and case '/'.
			 */
				if(IsEmpty(Character))
				{
					printf("[if*]");
					Push(Character,ptinputchar,1);
				}
				else
				{
					printf("[else*]");
					while(!IsEmpty(Character))
					{
						ptcurchar=Pop(Character);
						if(*ptcurchar=='('||*ptcurchar=='+'||*ptcurchar=='-')
						{
							Push(Character,ptcurchar,1);
							break;
						}
						else
						{
							Add(Output,ptcurchar,1);
						}
					}
					Push(Character,ptinputchar,1);
				}
				ifnum=0;
				ifpoint=0;
				break;
			case '(': 
				Push(Character,ptinputchar,1);
				ifnum=0;
				ifpoint=0;
				break;
			case ')': 
			/*
			 * Execute when ')' is taken in.
			 * '(' will only pair with '('
			 */
				if(IsEmpty(Character))
				{
					;
				}
				else
				{
					while(!IsEmpty(Character))
					{
						ptcurchar=Pop(Character);
						if(*ptcurchar=='(')
						{
							break;
						}
						else
						{
							Add(Output,ptcurchar,1);
						}
					}
				}
				ifnum=0;
				ifpoint=0;
				break;
			
			
			{			
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			/*
			 * Execute when a number is taken in.
			 * When no previous operator is stored in Character Stack,
			 * it will pop two numbers in the Number Stack, and store them in
			 * the output correspondingly. Meaning the '+'/'-' operator will 
			 * act on them. 
			 * Otherwise, the operator with higher precedence will be precess
			 * first.
			 */
				ptinputnum=(double*)malloc(sizeof(double)); 
				if(ifnum)
				{
					ptinputnum=TakeTail(Output);
					if(ifpoint<0)
					{
						*ptinputnum+=(*ptinputchar-'0')*pow(10,ifpoint);
						ifpoint--;
					}
					else
					{
						printf("Position:%d",ptinputnum);
						printf("BeforePack: %lf",*(double*)ptinputnum);
						*ptinputnum=10.0*(*ptinputnum)+(double)(*ptinputchar-'0');
						printf("Pack: %lf; %d times",*(double*)ptinputnum,i++);
					}
					AddTail(Output,ptinputnum,0);
				}
				else
				{
					*ptinputnum=(*ptinputchar-'0');
					Add(Output,ptinputnum,0);
					printf("Stack: %lf",*(double*)ptinputnum);
				}
				free(ptinputchar);
				ifnum=1;
				break;
				
			case '.': 
				ptinputnum=(double*)malloc(sizeof(double));
				if(ifpoint)
				{
					;
				}
				else
				{
					if(ifnum)
					{
						ifpoint=-1;
					}
					else
					{
						*ptinputnum=0;
						Add(Output,ptinputnum,0);
						ifnum=1;
						ifpoint=-1;
					}
				}
				break;
			}
			
			
			/*
			The part supportting function still needs fixing.
			case 's':
				ptinputnum=(double*)malloc(sizeof(double));
				if(ifnum)
				{
					ptinputnum=TakeTail(Output);
					ptinputnum*=sin(*ptinputchar-'0');
					AddTail(Output,ptinputnum,0);
				}
				else
				{
					*ptinputnum=sin(*ptinputchar-'0');
					Add(Output,ptinputnum,0);
				}
				break;
			case 'c':
				ptinputnum=(double*)malloc(sizeof(double));
				if(ifnum)
				{
					ptinputnum=TakeTail(Output);
					ptinputnum*=cos(*ptinputchar-'0');
					AddTail(Output,ptinputnum,0);
				}
				else
				{
					*ptinputnum=cos(*ptinputchar-'0');
					Add(Output,ptinputnum,0);
				}
				break;
			case 'l':
				ptinputnum=(double*)malloc(sizeof(double));
				if(ifnum)
				{
					ptinputnum=TakeTail(Output);
					ptinputnum*=log(*ptinputchar-'0');
					AddTail(Output,ptinputnum,0);
				}
				else
				{
					*ptinputnum=log(*ptinputchar-'0');
					Add(Output,ptinputnum,0);
				}
				break;
			case 'e':
				ptinputnum=(double*)malloc(sizeof(double));
				if(ifnum)
				{
					ptinputnum=TakeTail(Output);
					ptinputnum*=exp(*ptinputchar-'0');
					AddTail(Output,ptinputnum,0);
				}
				else
				{
					*ptinputnum=exp(*ptinputchar-'0');
					Add(Output,ptinputnum,0);
				}

			*/
			
			case '\n': 
				while(!IsEmpty(Character))
				{
					ptinputchar=(char*)malloc(sizeof(char)); 
					ptinputchar=Pop(Character);
					Add(Output,ptinputchar,1);
				}
				ifinput=0;
					/*
					 * set ifinput to 0 to end the input.
					 */
				break;
		}
	}

	DisposeStack(Character);

	Number=NewStack();
	Character=NewStack();
	
	ptinputchar=(char*)malloc(sizeof(char)); 
	while(!IsEmptyL(Output))
	{
		ptinputnum=(double*)malloc(sizeof(double)); 
		if(Output->head->type)
		{
			ptinputchar=Take(Output);
			switch(*(char*)ptinputchar)
			{
				case '+': 
					pta=Pop(Number);
					ptb=Pop(Number);
					*ptinputnum=*pta+*ptb;
					Push(Number, ptinputnum, 0);
					break;
				case '-': 
					pta=Pop(Number);
					ptb=Pop(Number);
					*ptinputnum=*pta-*ptb;
					Push(Number, ptinputnum, 0);
					break;
				case '*': 
					pta=Pop(Number);
					ptb=Pop(Number);
					*ptinputnum=(*pta)*(*ptb);
					Push(Number, ptinputnum, 0);
					break;
				case '/': 
					pta=Pop(Number);
					ptb=Pop(Number);
					if(*pta)
					{
						*ptinputnum=(*ptb)/(*pta);
						Push(Number, ptinputnum, 0);
					}
					else
					{
						printf("Cannot divided by ZERO!");
					}
					break;
				default: 
					printf("WRONG!"); 
					break;
			}
		}
		else
		{
			printf("---");
			ptinputnum=(double*)Take(Output);
			printf("add to output: %lf",*(double*)ptinputnum);
			Push(Number, ptinputnum, 0);
			printf("Pro: %d",ptinputnum);
		}	
	}
	
	ptresult=(double*)Pop(Number);
	printf("Answer: %lf",*(double*)ptresult);
	
	DisposeStack(Character);
	DisposeStack(Number);
	Delete(Output);

}



Stack NewStack(void)
{
	Stack S;
	S=(Stack)malloc(sizeof(struct node));
	S->next=NULL;
	return S;
}

void *Pop(Stack S)
{
	Stack Temp;
	void *ele;
	if(IsEmpty(S))
	{
		printf("Empty");
		return NULL;
	}
	Temp=S->next;
	ele=Temp->obj;
	S->next=S->next->next;
	free(Temp);
	return ele;
}

void Push(Stack S, void *ele, int type)
{
	Stack Temp;
	Temp=NewStack();
	Temp->obj=ele;
	Temp->next=S->next;
	Temp->type=type;
	S->next=Temp;
		
}

int IsEmpty(Stack S)
{
	return S->next==NULL;	
}

void DisposeStack(Stack S)
{
	while(!IsEmpty(S))
	{
		Pop(S);
	}
}

void *TopEle(Stack S)
{
	Stack Top;
	if(IsEmpty(S))
	{
		return NULL;
	}
	else
	{
		Top=Pop(S);
		Push(S,Top,0);
		return Top;
	}

}


List NewList(void)
{
	List L;
	L=(List)malloc(sizeof(struct linkedlist));
	L->head=NULL;
	L->tail=NULL;
	return L;
}

void *Take(List L)
{
	void * ele;
	ele=L->head->obj;
	L->head=L->head->next;
	return ele;
}

void *TakeTail(List L)
{
	void * ele;
	ele=L->tail->obj;
	return ele;
	
}

void Add(List L, void *ele, int type)
{
	Stack Temp;
	Temp=NewStack(); 
	Temp->obj=ele;
	Temp->type=type; 
	Temp->next=NULL;
	if(IsEmptyL(L))
	{
		L->head=Temp;
		L->tail=Temp;
	}
	else
	{
		if(L->head->next==NULL)
		{
			L->head->next=L->tail;
		}
		L->tail->next=Temp;
		L->tail=Temp;
	}
	
}

void AddTail(List L, void *ele, int type)
{
	L->tail->obj=ele;
}

int IsEmptyL(List L)
{
	return L->head==NULL;
}

void Delete(List L)
{
	void * temp;
	while(!IsEmptyL(L))
	{
		temp=L->head;
		L->head=L->head->next;
		free(temp); 
	}
}
