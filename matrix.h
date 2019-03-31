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
	double ** r[row];
}

void Matrix();
Matrix NewMatrix(int row, int column);

void Add(Matrix A, Matrix B, Matrix Result);
void Sub(Matrix A, Matrix B, Matrix Result);
void Mutli(Matrix A, Matrix B, Matrix Result);
void Inv(Matrix A, Matrix Result);
double Adj(Matrix A, int row, int column, Matrix Result);
double Det(Matrix A);



#endif
