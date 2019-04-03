#ifndef _matrix_h
#define _matrix_h

/*
 * linked list implementation of stakes
 */
struct Mat;
typedef struct Mat *ptm;
typedef ptm Matrix;

struct Mat
{
	int row;
	int column;
	double ** num;
};

/*
 * Functions definition, used to create Matrix ADT
 */
void MatrixP(void);
Matrix NewMatrix(int row, int column);
Matrix InputMatrix(void);
void PrintMatrix(Matrix Result);

/*
 * Functions used to cauculate objects
 */
Matrix AddM(Matrix A, Matrix B);
Matrix Sub(Matrix A, Matrix B);
Matrix Mutli(Matrix A, Matrix B);
Matrix Inv(Matrix A);
Matrix Adj(Matrix A, int row, int column);
double Det(Matrix A);



#endif
