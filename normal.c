/*
 * File:normal.c the code for a normal cauculator.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"normal.h"


void Normal()
{
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
	List SinS, CosS, LogS, ExpS;
			/*
			 * These Stacks are used to store numbers and operators inside a 
			 * function expression.
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
					Push(Character,ptinputchar,1);
				}
				else
				{
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
					Push(Character,ptinputchar,1);
				}
				else
				{
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
						*ptinputnum=10.0*(*ptinputnum)+(double)(*ptinputchar-'0');
					}
					AddTail(Output,ptinputnum,0);
				}
				else
				{
					*ptinputnum=(*ptinputchar-'0');
					Add(Output,ptinputnum,0);
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
			
			
			
			case 's':
				SinS=NewList();
				SinS=InputSin(SinS, Output);
				break;
			case 'c':
				CosS=NewList();
				CosS=InputCos(CosS, Output);
				break;
			case 'l':
				LogS=NewList();
				LogS=InputLog(LogS, Output);
				break;
			case 'e':
				ExpS=NewList();
				ExpS=InputExp(ExpS, Output);
				break;


			
			
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
		switch(Output->head->type)
		{
			case 1:	
				/*
				 * If the object is a operator.
				 */
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
			break;

			case 0:
				/*
				 * If the object is a number.
				 */
			ptinputnum=(double*)Take(Output);
			Push(Number, ptinputnum, 0);
			break;

			case 2:
				/*
				 * The object is an sin function-indicator.
				 */
			SinS=Take(Output);
			*ptinputnum=CauculateInverse (SinS);
			*ptinputnum=sin(*ptinputnum);
			Push(Number, ptinputnum, 0);
			break;
			
			case 3:
				/*
				 * The object is an cos function-indicator.
				 */
			CosS=Take(Output);
			*ptinputnum=CauculateInverse (CosS);
			*ptinputnum=cos(*ptinputnum);
			Push(Number, ptinputnum, 0);
			break;
			
			case 4:
				/*
				 * The object is an log function-indicator.
				 */
			LogS=Take(Output);
			*ptinputnum=CauculateInverse (LogS);
			*ptinputnum=log(*ptinputnum);
			Push(Number, ptinputnum, 0);
			break;
			
			case 5:
				/*
				 * The object is an exp function-indicator.
				 */
			ExpS=Take(Output);
			*ptinputnum=CauculateInverse (ExpS);
			*ptinputnum=exp(*ptinputnum);
			Push(Number, ptinputnum, 0);
			break;
			
			//pow remains to be modified
			
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
	L->tail->type=type;
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


List InputSin(List SinS, List Output)
{
	char a;
	scanf("%c",&a);
	if(a=='i')
	{
		;
	}
	else
	{
		return NULL;
	}
	scanf("%c",&a);
	if(a=='n')
	{
		;
	}
	else
	{
		return NULL;
	}
	TurnToInverse (SinS);
	Add(Output, SinS, 2);
	SinS=NewList();
	return SinS;
	
}

List InputCos(List CosS, List Output)
{
	char a;
	scanf("%c",&a);
	if(a=='o')
	{
		;
	}
	else
	{
		return NULL;
	}
	scanf("%c",&a);
	if(a=='s')
	{
		;
	}
	else
	{
		return NULL;
	}
	TurnToInverse (CosS);
	Add(Output, CosS, 3);
	CosS=NewList();
	return CosS;
	
}

List InputLog(List LogS, List Output)
{
	char a;
	scanf("%c",&a);
	if(a=='o')
	{
		;
	}
	else
	{
		return NULL;
	}
	scanf("%c",&a);
	if(a=='g')
	{
		;
	}
	else
	{
		return NULL;
	}
	TurnToInverse (LogS);
	Add(Output, LogS, 4);
	LogS=NewList();
	return LogS;
	
}

List InputExp(List ExpS, List Output)
{
	char a;
	scanf("%c",&a);
	if(a=='x')
	{
		;
	}
	else
	{
		return NULL;
	}
	scanf("%c",&a);
	if(a=='p')
	{
		;
	}
	else
	{
		return NULL;
	}
	TurnToInverse (ExpS);
	Add(Output, ExpS, 5);
	ExpS=NewList();
	return ExpS;
	
}

void TurnToInverse (List Output)
{
	double inputnum, result;
	double *ptinputnum=&inputnum, *ptresult=&result;
	int ifnum=0,ifpoint=0,ifinput=1;
	char inputchar, curchar;
	char *ptinputchar=&inputchar, *ptcurchar=&curchar;
	Stack Character;
	List SinS, CosS, LogS, ExpS;
	Character=NewStack();
	
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
					Push(Character,ptinputchar,1);
				}
				else
				{
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
					Push(Character,ptinputchar,1);
				}
				else
				{
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
					return;
				}
				else
				{
					while(!IsEmpty(Character))
					{
						ptcurchar=Pop(Character);
						if(*ptcurchar=='(')
						{
							if(IsEmpty(Character))
							{
								return;
							}
							/*
							 * determine whether this function expression is ended.
							 */
							break;
						}
						else
						{
							Add(Output,ptcurchar,1);
						}
					}
					return;
				}
				ifnum=0;
				ifpoint=0;
				break;
			
			
			
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
						*ptinputnum=10.0*(*ptinputnum)+(double)(*ptinputchar-'0');
					}
					AddTail(Output,ptinputnum,0);
				}
				else
				{
					*ptinputnum=(*ptinputchar-'0');
					Add(Output,ptinputnum,0);
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
			
			case 's':
				SinS=NewList();
				SinS=InputSin(SinS, Output);
				break;
			case 'c':
				CosS=NewList();
				CosS=InputCos(CosS, Output);
				break;
			case 'l':
				LogS=NewList();
				LogS=InputLog(LogS, Output);
				break;
			case 'e':
				ExpS=NewList();
				ExpS=InputExp(ExpS, Output);
				break;


			default:
				break;
		}
	}
	return;
}

double CauculateInverse (List Output)
{
	Stack Number;
	List SinS, CosS, LogS, ExpS;
	double inputnum, result, a, b;
	double *ptinputnum=&inputnum, *ptresult=&result, *pta=&a, *ptb=&b;
	int ifnum=0,ifpoint=0,ifinput=1;
	char inputchar, curchar;
	char *ptinputchar=&inputchar, *ptcurchar=&curchar;

	Number=NewStack();
	
	ptinputchar=(char*)malloc(sizeof(char)); 
	while(!IsEmptyL(Output))
	{
		ptinputnum=(double*)malloc(sizeof(double)); 
		switch(Output->head->type)
		{
			case 1:	
					/*
					 * If the object is a operator.
					 */
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
				break;

			case 0:
					/*
					 * If the object is a number.
					 */
				ptinputnum=(double*)Take(Output);
				Push(Number, ptinputnum, 0);
				break;

			
			case 2:
					/*
					 * The object is an sin function-indicator.
					 */
				SinS=Take(Output);
				*ptinputnum=CauculateInverse (SinS);
				*ptinputnum=sin(*ptinputnum);
				Push(Number, ptinputnum, 0);
				break;
				
			case 3:
					/*
					 * The object is an cos function-indicator.
					 */
				CosS=Take(Output);
				*ptinputnum=CauculateInverse (CosS);
				*ptinputnum=cos(*ptinputnum);
				Push(Number, ptinputnum, 0);
				break;
				
			case 4:
					/*
					 * The object is an log function-indicator.
					 */
				LogS=Take(Output);
				*ptinputnum=CauculateInverse (LogS);
				*ptinputnum=log(*ptinputnum);
				Push(Number, ptinputnum, 0);
				break;
				
			case 5:
					/*
					 * The object is an exp function-indicator.
					 */
				ExpS=Take(Output);
				*ptinputnum=CauculateInverse (ExpS);
				*ptinputnum=exp(*ptinputnum);
				Push(Number, ptinputnum, 0);
				break;
								
			
		}
	}
	
	
	ptresult=(double*)Pop(Number);
	return *ptresult;
}
