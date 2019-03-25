#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"normal.h"

Stack Temp;

void Normal()
{
	double inputnum, result=999, a, b;
	double *ptinputnum=&inputnum, *ptresult=&result, *pta=&a, *ptb=&b;
	char *ptinputchar,*ptcurchar;
	int ifnum=0,ifpoint=0,ifinput=1;
	Stack Number, Character, Output;
	Number=NewStack();
	Character=NewStack();
	Output=NewStack();
		
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
							Push(Output,ptcurchar,1);
						}
					}
					Push(Character,ptinputchar,1);
				}
				printf("[+]");
				ifnum=0;
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
							Push(Output,ptcurchar,1);
						}
					}
					//Push(Character,ptinputchar,1);
				}
				ifnum=0;
				break;
			case '(': 
				Push(Character,ptinputchar,1);
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
							Push(Output,ptcurchar,1);
						}
					}
				}
				ifnum=0;
				break;
			
			//input numbers case 0~9, '.'
			{			
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				ptinputnum=(int*)malloc(sizeof(int)); 
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
					Push(Number,ptinputnum,0);
				}
				else
				{
					*ptinputnum=(*ptinputchar-'0');
					Push(Number,ptinputnum,0);
				}
				free(ptinputchar);
				ifnum=1;
				break;
				
			case '.': 
				ptinputnum=(int*)malloc(sizeof(int));
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
						Push(Number,ptinputnum,0);
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
				ifinput=0;	//end the input
				break;
			
			
			
		}
		
		
	}

	
	//PrintStack(Number);
	//PrintStack(Character);
	PrintStack(Output);
	
	
	
	
	
	
	
	//Calculate
	// Stack output			*ptresult=&result
/*	ptinputchar=(char*)malloc(sizeof(char)); 
	while(!IsEmpty(Output))
	{
		ptinputnum=(int*)malloc(sizeof(int)); 
		if(Output->type)			//1, character
		{
			ptinputchar=Pop(Output);
			switch(*ptinputchar)
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
					*ptinputnum=*pta+*ptb;
					Push(Number, ptinputnum, 0);
					break;
				case '*': 
					pta=Pop(Number);
					ptb=Pop(Number);
					*ptinputnum=*pta+*ptb;
					Push(Number, ptinputnum, 0);
					break;
				case '/': 
					pta=Pop(Number);
					ptb=Pop(Number);
					*ptinputnum=*pta+*ptb;
					Push(Number, ptinputnum, 0);
					break;
			}
			Output=Output->next;
		}
		else
		{
			ptinputnum=Pop(Output);
			Push(Number, ptinputnum, 0);
			
			
		}
		s
	
	}
*/		
	if(!IsEmpty(Number))
	{
		printf("Error");
	}
	else
	{
		ptresult=Pop(Number);
		printf("Answer: %lf",*ptresult);
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

void Push(Stack S, void *ele, int type)
{
	printf("[push]");
	//Stack Temp;
	Temp=NewStack();
	Temp->obj=ele;
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
		Push(S,Top,0);
		return Top;
	}

}


void PrintStack(Stack S)
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
