/*
 * File:poly.c the code for the cauculation of polynomials.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"poly.h"

void Poly()
{
	int mode=1;
		/*
		 * Mark the input position.
		 * =1 when we are out of the pair (coefficient, time),
		 * =2 when taking coefficient, =3 when taking time, 
		 * =0 to quit.
		 */
	char input;
	double coefficient=0,time=0;
	Listp Poly1, Poly2, Result;
		/*
		 * list to store polynomial
		 */
	
	/*
	 * read the input of the first polynomial and store it in a listed list
	 */
	Poly1=NewListp();
	printf("Please enter the first polynomial:");
	getchar(); 
	while(mode)
	{
		scanf("%c",&input);
		switch(input)
		{
			case '(':
				mode=2;
				break;
			case ')':
				mode=1;
				AddByTime(Poly1, coefficient, time);
				coefficient=0;
				time=0;
				break;
			case ',':
				mode=3;
				break;
			case '\n':
				mode=0;
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				if(mode==2)
				{
					coefficient=10*coefficient+(input-'0');
				}
				else if(mode==3)
				{
					time=10*time+(input-'0');
				}
				break;
			default:
				break;	
			
		}
	}
	
	
	/*
	 * read the input of the second polynomial and store it in a listed list
	 */
	Poly2=NewListp();
	printf("Please enter the second polynomial:");
	mode=1;
	coefficient=0;
	time=0;
	while(mode)
	{
		scanf("%c",&input);
		switch(input)
		{
			case '(':
				mode=2;
				break;
			case ')':
				mode=1;
				AddByTime(Poly2, coefficient, time);
				coefficient=0;
				time=0;
				break;
			case ',':
				mode=3;
				break;
			case '\n':
				mode=0;
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				if(mode==2)
				{
					coefficient=10*coefficient+(input-'0');
				}
				else if(mode==3)
				{
					time=10*time+(input-'0');
				}
				break;
			default:
				break;	
			
		}
	}


	Result=MultiPoly(Poly1,Poly2);
		/*
		 * Multiply two of the polynomials and store the result in
		 * the Result listed list ADT.
		 */
	PrintPoly(Result);
	
}



ptpn NewNode(void)
{
	ptpn p;
	p=(ptpn)malloc(sizeof(struct polynode));
	p->next=NULL;
	p->coefficient=0;
	p->time=0;
	return p;	
}

Listp NewListp(void)
{
	Listp L;
	L=(Listp)malloc(sizeof(struct linkedlistp));
	L->head=NULL;
	L->tail=NULL;
	return L;
}

ptpn Takep(Listp L)
{
	ptpn ele;
	ele=L->head;
	L->head=L->head->next;
	return ele;
}

void AddByTime(Listp L, double coefficient, double time)
{
	ptpn fore, back, add;
	add=NewNode();
	if(IsEmptyLp(L))
	{
		add->coefficient=coefficient;
		add->time=time;
		add->next=NULL;
		L->head=add;
	}
	else
	{
		fore=L->head->next;
		back=L->head;
		if(fore==NULL)
		{
			if(back->time>time)
			{
				add->coefficient=coefficient;
				add->time=time;
				add->next=back;
				L->head=add;
			}
			else if(back->time==time)
			{
				back->coefficient+=coefficient;
			}
			else if(back->time<time)
			{
				add->coefficient=coefficient;
				add->time=time;
				add->next=NULL;
				back->next=add;
			}
		}
		else
		{
			while((fore->time)<time)
			{
				if(fore->next==NULL)
				{
					break;
				}
				back=fore;
				fore=fore->next;
			}
			if(fore->time>time)
			{
				add->coefficient=coefficient;
				add->time=time;
				add->next=fore;
				back->next=add;
			}
			else if(fore->time==time)
			{
				fore->coefficient+=coefficient;
			}
			else if(fore->time<time)
			{
				add->coefficient=coefficient;
				add->time=time;
				add->next=NULL;
				fore->next=add;
			}
			
		}	
	}
}

int IsEmptyLp(Listp L)
{
	return L->head==NULL;
}

void Deletep(Listp L)
{
	void * temp;
	while(!IsEmptyLp(L))
	{
		temp=L->head;
		L->head=L->head->next;
		free(temp); 
	}
}

void PrintPoly(Listp L)
{
	Listp Temp=L;
	while(!IsEmptyLp(L))
	{
		printf("%lf",L->head->coefficient);
		printf("x^%lf",L->head->time);
		L->head=L->head->next;
		if(!IsEmptyLp(L))
		{
			printf("+");
		}
	}
	L=Temp;
	
}


Listp MultiPoly(Listp Poly1, Listp Poly2)
{
	ptpn node1, node2, t;
	ptpn *temp;
	Listp Result;
	Result=NewListp();
	node1=Poly1->head;
	while(!(node1==NULL))
	{
		t=(Poly2->head);
		temp=&t;
		while(!(*temp==NULL))
		{
			node2=*temp;
			AddByTime(Result, node1->coefficient*node2->coefficient, node1->time*node2->time);
			*temp=(*temp)->next;	
		}
		node1=node1->next;
	}
	return Result;
}
