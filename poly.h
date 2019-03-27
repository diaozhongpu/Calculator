#ifndef _poly_h
#define _poly_h

//linked list implementation of stakes
struct polynode;
typedef struct polynode *ptpn;

struct polynode
{
	double coefficient;
	double time;
	ptpn next;
};


typedef struct linkedlistp *Listp;
struct linkedlistp
{
	ptpn head;
	ptpn tail;
};

ptpn NewNode(void);
Listp NewListp(void);
ptpn Takep(Listp L);
void AddByTime(Listp L, double coefficient, double time);
int IsEmptyLp(Listp L);
void Deletep(Listp L);
void PrintPoly(Listp L);

void Poly(void);
Listp MultiPoly(Listp Poly1, Listp Poly2);


#endif
