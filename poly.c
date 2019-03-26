#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"poly.h"

void Poly()
{
	int mode=1;
		//1 for out(c,t), 2 for take coefficient, 3 for time, 0 to quit.
	char input;
	double coefficient=0,time=0;
	List Poly1, Poly2, Result;
	
	Poly1=NewList();
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
	//PrintPoly(Poly1);
	
	
	
	Poly2=NewList();
	printf("\nPlease enter the second polynomial:");
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
	//PrintPoly(Poly2);	


	Result=MultiPoly(Poly1,Poly2);
	PrintPoly(Result);
	
}



ptr NewNode(void)
{
	ptr p;
	p=(ptr)malloc(sizeof(struct node));
	p->next=NULL;
	p->coefficient=0;
	p->time=0;
	return p;	
}

List NewList(void)
{
	List L;
	L=(List)malloc(sizeof(struct linkedlist));
	L->head=NULL;
	L->tail=NULL;
	return L;
}

ptr Take(List L)
{
	ptr ele;
	ele=L->head;
	L->head=L->head->next;
	return ele;
}

void AddByTime(List L, double coefficient, double time)
{
	ptr fore, back, add;
	add=NewNode();
	if(IsEmptyL(L))
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

void PrintPoly(List L)
{
	List Temp=L;
	while(!IsEmptyL(L))
	{
		printf("%lf",L->head->coefficient);
		printf("x^%lf",L->head->time);
		L->head=L->head->next;
		if(!IsEmptyL(L))
		{
			printf("+");
		}
	}
	L=Temp;
	
}


List MultiPoly(List Poly1, List Poly2)
{
	ptr node1, node2, t;
	ptr *temp;
	List Result;
	Result=NewList();
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
