#ifndef _poly_h
#define _poly_h

//linked list implementation of stakes
struct node;
typedef struct node *ptr;

struct node
{
	double coefficient;
	double time;
	ptr next;
};


typedef struct linkedlist *List;
struct linkedlist
{
	ptr head;
	ptr tail;
};

ptr NewNode(void);
List NewList(void);
ptr Take(List L);
void AddByTime(List L, double coefficient, double time);
int IsEmptyL(List L);
void Delete(List L);
void PrintPoly(List L);

void Poly(void);
List MultiPoly(List Poly1, List Poly2);


#endif
