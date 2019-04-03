#ifndef _normal_h
#define _normal_h

/*
 * linked list implementation of stakes
 */
struct node;
typedef struct node *ptr;
typedef ptr Stack;

struct node
{
	int type;
	/*
	 * linked list implementation of stakes
	 * 0 for number, 1 for character
	 */
	void *obj;
	/*
	 * pointer to the datum
	 */
	ptr next;
};


/*
 * Listed list ADT defination
 */
typedef struct linkedlist *List;
struct linkedlist
{
	ptr head;
	ptr tail;
};

void Normal(void);

/*
 * Below are typical functions for Stack ADT.
 */
Stack NewStack(void);
void *Pop(Stack S);
void Push(Stack S, void *ele, int type);
int IsEmpty(Stack S);
void DisposeStack(Stack S);

void *TopEle(Stack S);

/*
 * Below are typical functions for linked list ADT.
 */
List NewList(void);
void *Take(List L);
void *TakeTail(List L);
	/*
	 * Take the element at the tail of a list.
	 */
void Add(List L, void *ele, int type);
void AddTail(List L, void *ele, int type);
	/*
	 * Add an element at the tail of a list.
	 */
int IsEmptyL(List L);
void Delete(List L);

/*
 * Special functions used to make this application able to
 * handle expreesion inside a function.
 */
List InputSin(List SinS, List Output);
List InputCos(List CosS, List Output);
List InputLog(List LogS, List Output);
List InputExp(List ExpS, List Output);
List InputPow(List PowS, List Output);

List CauSin(List SinS);
List CauCos(List CosS);
List CauLog(List LogS);
List CauExp(List ExpS);
List CauPow(List PowS);

/*
 * Functions used to concstruct inverse expression and
 * cauculate the value of this expression.
 */
void TurnToInverse (List Output);
double CauculateInverse (List Output);

#endif