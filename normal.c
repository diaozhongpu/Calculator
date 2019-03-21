#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"normal.h"

Stack Temp;

void Normal()
{
	double inputnum, result;
	double a,b;
	double *ptinputnum=&inputnum, *ptresult=&result;
	char inputchar,curchar;
	char *ptinputchar=&inputchar,*ptcurchar=&curchar;
	int ifnum=0,ifpoint=0,ifinput=1;
	Stack Number, Character, Output;
	Number=NewStack();
	Character=NewStack();
	Output=NewStack();
		
	getchar();
	printf("Please input:");
	while(ifinput)
	{
		scanf("%c",ptinputchar);
		//printf("%c",*ptinputchar);
		switch(*ptinputchar)
		{
			case '+': case '-':
				if(IsEmpty(Character))
				{
					printf("[if]");
					Push(Character,ptinputchar);
				}
				else
				{
					printf("[else]");
					while(!IsEmpty(Character))
					{
						ptcurchar=Pop(Character);
						if(*ptcurchar=='(')
						{
							Push(Character,ptcurchar);
							break;
						}
						else
						{
							Push(Output,ptcurchar);
						}
					}
					Push(Character,ptinputchar);
				}
				printf("[+]");
				ifnum=0;
				break;
			case '*': case '/': 
				if(IsEmpty(Character))
				{
					printf("[if*]");
					Push(Character,ptinputchar);
				}
				else
				{
					printf("[else*]");
					while(!IsEmpty(Character))
					{
						ptcurchar=Pop(Character);
						if(*ptcurchar=='('||*ptcurchar=='+'||*ptcurchar=='-')
						{
							Push(Character,ptcurchar);
							break;
						}
						else
						{
							Push(Output,ptcurchar);
						}
					}
					Push(Character,ptinputchar);
				}
				ifnum=0;
				break;
			case '(': 
				Push(Character,ptinputchar);
				ifnum=0;
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
							Push(Output,ptcurchar);
						}
					}
				}
				ifnum=0;
				break;
			
			//input numbers case 0~9, '.'
			{			
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				if(ifnum)
				{
					ptinputnum=Pop(Number);
					if(ifpoint<0)
					{
						*ptinputnum+=(*ptinputchar-'0')*pow(10,ifpoint);
						ifpoint--;
					}
					else
					{
						*ptinputnum=10*(*ptinputnum)+(*ptinputchar-'0');
					}
				//	printf("[%f]",*ptinputnum);
					Push(Number,ptinputnum);
				}
				else
				{
					*ptinputnum=(*ptinputchar-'0');
					Push(Number,ptinputnum);	
				}
				ifnum=1;
				break;
				
			case '.': 
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
						Push(Number,ptinputnum);
						ifnum=1;
						ifpoint=-1;
					}
				}
				break;
			}
			
			case 's':
			case 'c':
			case 'l':
			case 'e':
			
			case '\n': 
				ifinput=0;
				break;
			
			
			
		}
		
		
	}

	
	//PrintStack(Number);
	//PrintStack(Character);
	PrintStack(Output);
	
	
	
	
	
	
	//Calculate
	// Stack output			*ptresult=&result
	while(!IsEmpty(Output))
	{
		if(Output->type)			//1, character
		{
			ptinputchar=Pop(Output);
			switch(*ptinputchar)
			{
				case '+': break;
			}
			Output=Output->next;
		}
		else
		{
			ptinputnum=Pop(Output);
		}
		
		
	}
	
	
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

void Push(Stack S, void *ele)
{
	printf("[push]");
	//Stack Temp;
	void *tempele;
	Temp=NewStack();
	Temp->obj=tempele;
	printf("[$$%d]",Temp->obj);
	Temp->next=S->next;
	printf("[$$%d]",Temp->next);
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
		//Empty Stack
	}
	else
	{
		Top=Pop(S);
		Push(S,Top);
		return Top;
	}

}


void PrintStack(Stack S)
{
	Temp=S;
	while(!(Temp->next==NULL))
	{
		printf("[printf]");
		Temp=Temp->next;
		printf("[##%d]",Temp->next);
		//printf("%lf",*((double *)S->obj));
		printf("%c",*((char *)Temp->obj));
		printf("[%d]",Temp->obj);
	}
	
}
