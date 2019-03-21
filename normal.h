#ifndef _normal_h
#define _normal_h

//linked list implementation of stakes
struct node;
typedef struct node *ptr;
typedef ptr Stack;

struct node
{
	int type; //0 for number, 1 for character
	void *obj;
	ptr next;
};

Stack NewStack(void);
void *Pop(Stack S);
void Push(Stack S, void *ele);
int IsEmpty(Stack S);
void DisposeStack(Stack S);

void *TopEle(Stack S);
void PrintStack(Stack S);

void Normal(void);

#endif
