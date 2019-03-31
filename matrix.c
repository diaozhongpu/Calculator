/*
 * File:matrix.c the code for a matrix cauculator.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"matrix.h"


void Matix()
{
	Matrix A, B, Result;

}


void Add(Matrix A, Matrix B, Matrix Result)
{
	int rn,cn;
	if(A->row==B->row&&A->column==B->column)
	{
		Result=NewMatrix(row)
		for(rn=0;rn<A->row;rn++)
		{
			for(cn=0;cn<A->column;cn++)
			{
				(Result->r)[rn][cn]=(A->r)[rn][cn]+(B->r)[rn][cn];
			}
		}
	}
	else
	{
		printf("ERROR: cannot add two matrix with different row number or column number!");
	}
}

void Sub(Matrix A, Matrix B, Matrix Result)
{
	int rn,cn;
	if(A->row==B->row&&A->column==B->column)
	{
		Result=NewMatrix(A->row,B->column);
		for(rn=0;rn<A->row;rn++)
		{
			for(cn=0;cn<A->column;cn++)
			{
				(Result->r)[rn][cn]=(A->r)[rn][cn]-(B->r)[rn][cn];
			}
		}
	}
	else
	{
		printf("ERROR: cannot substute one matrix from another
			with different row number or column number!");
	}
}

void Mutli(Matrix A, Matrix B, Matrix Result)
{
	int rn, cn, i;
	if(A->row==B->row&&A->column==B->column)
	{
		Result=NewMatrix(A-row,B->column);
		for(rn=0;rn<Result->row;rn++)
		{
			for(cn=0;cn<Result->column;cn++)
			{
				(Result->r)[rn][cn]=0;
				for(i=0;i<A->column;i++)
				{
					(Result->r)[rn][cn]+=(A->r)[rn][i]*(B->r)[i][cn];
				}
				
			}
		}
	}
	else
	{
		printf("ERROR: cannot mutliply two matrix with different row number and column number!");
	}
}

void Inv(Matrix A, Matrix Result)
{
	int rn,cn;
	double det;
	if(A->row==A->column)
	{
		det=Det(A);
		if(det)
		{
			Result=NewMatrix(A->row, A->column);
			for(rn=0;rn<A->row;rn++)
			{
				for(cn=0;cn<A->column;cn++)
				{
					(Result->r)[rn][cn]=Adj(A,rn,cn)/det;
				}
			}
		}
		else
		{
			printf("Matirx A does not have an inverse matrix.")
		}
		
	}
	else
	{
		printf("ERROR: cannot inverse a matrix with different row number and column number!");
	}
}

double Adj(Matrix A, int row, int column)
{
	Matrix B;
	int rn, cn, rni, cni;
	B=NewMatrix(A->row-1, B->row-1);
	rni=0;
	for(rn=0;rn<A->row;rn++)
	{
		if(rn==row)
		{
			continue;
		}
		else
		{
			for(cn=0;cn<A->column;cn++)
			{
				(B->r)[rni][cni++]=(A->r)[rn][cn];
			}
		}
		rni++;
		cni=0;	
	}
	return Det(B);
}

double Det(Matrix A)
{
	double det=0;
	if(A->row==A->column)
	{
		if(A->row==1)
		{
			return (A->row)[0][0];
		}
		else
		{
			for(cn=0;cn<A->column;cn++)
			{
				det+=pow(-1,cn)*(A->row)[0][cn]*Det(Adj(A,0,cn));
			}
			return det;
		}
		
	}
	else
	{
		printf("The column number does not equal to row number.");
		return 0;
	}
}


Matrix NewMatrix(int row, int column)
{
	int i;
	Matrix=(*Mat)malloc(sizeof(Mat));
	Matrix->row=row;
	Matrix->column=column;
	Matrix->r=(double **)malloc(row*sizeof(double *));
	for(i=0;i<column;i++)
	{
		(Matrix->r)[i]=(double *)malloc(column*sizeof(double));
	}
	return Matrix;
}
