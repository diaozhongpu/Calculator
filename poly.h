#ifndef _poly_h
#define _poly_h


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

void Poly(void);

/*
 * Function: AddByTime();
 * Add new element to an existing list according to its time,
 * in order to sustain a rising order.
 */
void AddByTime(Listp L, double coefficient, double time);
int IsEmptyLp(Listp L);
void Deletep(Listp L);
void PrintPoly(Listp L);

/*
 * Function used to mutliply two polynomials.
 */
Listp MultiPoly(Listp Poly1, Listp Poly2);


#endif