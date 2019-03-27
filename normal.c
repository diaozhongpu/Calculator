//new normal

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"normal.h"

Stack Temp;

void Normal()
{
	int i=0;
	double inputnum, result=999, a, b;
	double *ptinputnum=&inputnum, *ptresult=&result, *pta=&a, *ptb=&b;
	char *ptinputchar,*ptcurchar;
	int ifnum=0,ifpoint=0,ifinput=1;
	Stack Number, Character;
	List Output;
	Number=NewStack();
	Character=NewStack();
	Output=NewList();
		
	getchar();
	printf("Please input:");
	while(ifinput)
	{
		ptinputchar=(char*)malloc(sizeof(char)); 
		scanf("%c",ptinputchar);
		//printf("%c",*ptinputchar);
		switch(*ptinputchar)
		{
			case '+': case '-':
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
			
			//input numbers case 0~9, '.'
			{			
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
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
			
			
					//functions			
			case 's':
			case 'c':
			case 'l':
			case 'e':

			
			case '\n': 
				while(!IsEmpty(Character))
				{
					ptinputchar=(char*)malloc(sizeof(char)); 
					ptinputchar=Pop(Character);
					Add(Output,ptinputchar,1);
				}
				ifinput=0;	//end the input
				break;
			
			
			
		}
		
		
	}



	//PrintList(Output); 
	
	
	//Calculate
	Number=NewStack();
	Character=NewStack();
	
	ptinputchar=(char*)malloc(sizeof(char)); 
		printf("2+++");
	while(!IsEmptyL(Output))
	{
		ptinputnum=(double*)malloc(sizeof(double)); 
		printf("@@");
		if(Output->head->type)			//1, character
		{
			ptinputchar=Take(Output);
			printf("Pro1: %d",ptinputnum);
			printf("+++");
			switch(*(char*)ptinputchar)
			{
				case '+': 
					pta=Pop(Number);
					ptb=Pop(Number);
					*ptinputnum=*pta+*ptb;
					Push(Number, ptinputnum, 0);
					printf("IN: %d",ptinputnum);
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
					*ptinputnum=(*ptb)/(*pta);
					Push(Number, ptinputnum, 0);
					break;
				default: 
					printf("WRONG!"); 
					break;
			}
			//Output->head=Output->head->next;
		}
		else
		{
			printf("---");
			ptinputnum=(double*)Take(Output);
			printf("add to output: %lf",*(double*)ptinputnum);
			Push(Number, ptinputnum, 0);
			printf("Pro: %d",ptinputnum);
			//Output->head=Output->head->next;
		}
		
	
	}
	
	printf("Answer: %d",ptresult);
	ptresult=(double*)Pop(Number);
	printf("Answer: %d",ptresult);
	printf("Answer: %lf",*(double*)ptresult);
	
	
}



static Stack NewStack(void)
{
	Stack S;
	S=(Stack)malloc(sizeof(struct node));
	S->next=NULL;
	return S;
}

static void *Pop(Stack S)
{
	printf("[pop]");
	void *ele;
	//Stack Temp;
	if(IsEmpty(S))
	{
		printf("Empty");
		return NULL;
		//Empty Stack
	}
	Temp=S->next;
	ele=Temp->obj;
	S->next=S->next->next;
	free(Temp);
	return ele;
}

static void Push(Stack S, void *ele, int type)
{
	printf("[push]");
	//Stack Temp;
	Temp=NewStack();
	Temp->obj=ele;
	Temp->next=S->next;
	Temp->type=type;
	S->next=Temp;
		
}

static int IsEmpty(Stack S)
{
	return S->next==NULL;	
}

static void DisposeStack(Stack S)
{
	while(!IsEmpty(S))
	{
		Pop(S);
	}
}

static void *TopEle(Stack S)
{
	Stack Top;
	if(IsEmpty(S))
	{
		return NULL;
		//Empty Stack
	}
	else
	{
		Top=Pop(S);
		Push(S,Top,0);
		return Top;
	}

}


static void PrintStack(Stack S)
{
	;
	/*
	while(IsEmpty(S))
	{
		printf("[printf]");
		S=S->next;
		if(S->type)
		{
			printf("[printf]");
			printf("%c",*((char*)S->obj));
		}
		else
		{
			printf("[print1f]");
			printf("[%lf]",*(double*)S->obj);
		}
		
		
	}
	*/
	
}

static List NewList(void)
{
	List L;
	L=(List)malloc(sizeof(struct linkedlist));
	L->head=NULL;
	L->tail=NULL;
	return L;
}

static void *Take(List L)
{
	void * ele;
/*	if(IsEmptyL(L))
	{
		printf("Empty!");
		return NULL;
	}
	else
	{*/
		ele=L->head->obj;
		L->head=L->head->next;
//	}
	return ele;
}

static void *TakeTail(List L)
{
	void * ele;
	ele=L->tail->obj;
	return ele;
	
}

static void Add(List L, void *ele, int type)
{
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

static void AddTail(List L, void *ele, int type)
{
	L->tail->obj=ele;
}

static int IsEmptyL(List L)
{
	return L->head==NULL;
}

static void Delete(List L)
{
	void * temp;
	while(!IsEmptyL(L))
	{
		temp=L->head;
		L->head=L->head->next;
		free(temp); 
	}
}

static void PrintList(List L)
{
	int type;
	while(!IsEmptyL(L))
	{
		type=L->head->type;	
		if(type)
		{
			printf("[!%c]",*(char*)L->head->obj);
		}
		else
		{
			printf("[!%lf]",*(double*)L->head->obj);
		}
		L->head=L->head->next;
	}
	
	
}

