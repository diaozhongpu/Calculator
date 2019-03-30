#ifndef _matrix_h
#define _matrix_h

//linked list implementation of stakes
struct Mat;
typedef Mat *ptm;
typedef ptm Matrix;

struct Mat
{
	int row;
	int column;
	
	
}



Matrix Add(Matrix A, Matrix B);
Matrix Sub(Matrix A, Matrix B);
Matrix Mutli(Matrix A, Matrix B);
Matrix Inv(Matrix A);
double Det(Matrix A);


void Matrix(void);



#endif
