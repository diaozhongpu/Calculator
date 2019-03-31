/*
 * File:matrix.c the code for a matrix cauculator.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"matrix.h"


void MatrixP(void)
{
	Matrix A, B, Result;
	double det;
	int mode;
	printf("Please enter the cauclulation you want to carry out:");
	printf("1=addition, 2=substitute, 3=mutliply\n");
	printf("4=determinant, 5=inversation, 0=quit\n");
	scanf("%d",&mode);
	switch(mode)
	{
		case 1:
			A=InputMatrix();
			B=InputMatrix();
			Result=AddM(A,B);
			break;
		case 2:
			A=InputMatrix();
			B=InputMatrix();
			Result=Sub(A,B);
			break;
		case 3:
			A=InputMatrix();
			B=InputMatrix();
			Result=Mutli(A,B);
			break;
		case 4:
			A=InputMatrix();
			det=Det(A);
			break;
		case 5:
			A=InputMatrix();
			Result=Inv(A);
			break;
		default:
			break;
	}
	if(mode==4)
	{
		printf("The determinant is %lf",det);
	}
	else if(mode==0)
	{
		;
	}
	else
	{
		PrintMatrix(Result);
	}
	
}


Matrix AddM(Matrix A, Matrix B)
{
	int rn,cn;
	Matrix Result;
	if(A->row==B->row&&A->column==B->column)
	{
		Result=NewMatrix(A->row, A->row);
		for(rn=0;rn<A->row;rn++)
		{
			for(cn=0;cn<A->column;cn++)
			{
				(Result->num)[rn][cn]=(A->num)[rn][cn]+(B->num)[rn][cn];
			}
		}
		return Result;
	}
	else
	{
		printf("ERROR: cannot add two matrix with different row number or column number!");
		return NULL;
	}
}

Matrix Sub(Matrix A, Matrix B)
{
	int rn,cn;
	Matrix Result;
	if(A->row==B->row&&A->column==B->column)
	{
		Result=NewMatrix(A->row,B->column);
		for(rn=0;rn<A->row;rn++)
		{
			for(cn=0;cn<A->column;cn++)
			{
				(Result->num)[rn][cn]=(A->num)[rn][cn]-(B->num)[rn][cn];
			}
		}
		return Result;
	}
	else
	{
		printf("ERROR: cannot substute one matrix from another with different row number or column number!");
		return NULL;
	}
}

Matrix Mutli(Matrix A, Matrix B)
{
	int rn, cn, i;
	Matrix Result;
	if(A->column==B->row)
	{
		Result=NewMatrix(A->row,B->column);
		for(rn=0;rn<Result->row;rn++)
		{
			for(cn=0;cn<Result->column;cn++)
			{
				(Result->num)[rn][cn]=0;
				for(i=0;i<A->column;i++)
				{
					(Result->num)[rn][cn]+=(A->num)[rn][i]*(B->num)[i][cn];
				}
				
			}
		}
		return Result;
	}
	else
	{
		printf("ERROR: cannot mutliply two matrix with different row number and column number!");
		return NULL;
	}
}

Matrix Inv(Matrix A)
{
	int rn,cn;
	double det;
	Matrix Result;
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
					(Result->num)[rn][cn]=Det(Adj(A,rn,cn))/det;
				}
			}
			return Result;
		}
		else
		{
			printf("Matirx A does not have an inverse matrix.");
			return NULL;
		}
		
	}
	else
	{
		printf("ERROR: cannot inverse a matrix with different row number and column number!");
		return NULL;
	}
}

Matrix Adj(Matrix A, int row, int column)
{
	Matrix Result;
	int rn, cn, rni, cni;
	Result=NewMatrix(A->row-1, A->row-1);
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
				if(cn==column)
				{
					continue;
				}
				else
				{
					(Result->num)[rni][cni++]=(A->num)[rn][cn];
				}
			}
		}
		rni++;
		cni=0;	
	}
	return Result;
}

double Det(Matrix A)
{
	int cn;
	double det=0;
	if(A->row==A->column)
	{
		if(A->row==1)
		{
			return (A->num)[0][0];
		}
		else
		{
			for(cn=0;cn<A->column;cn++)
			{
				det+=pow(-1,cn)*(A->num)[0][cn]*Det(Adj(A,0,cn));
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
	Matrix Temp;
	Temp=(Matrix)malloc(sizeof(struct Mat));
	Temp->row=row;
	Temp->column=column;
	Temp->num=(double **)malloc(row*sizeof(double *));
	for(i=0;i<column;i++)
	{
		(Temp->num)[i]=(double *)malloc(column*sizeof(double));
	}
	return Temp;
}

Matrix InputMatrix(void)
{
	Matrix Temp;
	int row,column;
	printf("Please enter the mmatrix:\n");
	printf("Please enter its numner of rows:\n");
	scanf("%d",&row);
	printf("Please enter its numner of columns:\n");
	scanf("%d",&column);
	Temp=NewMatrix(row,column);
	printf("Enter the entities, up to down, left to right:\n");
	for(row=0;row<Temp->row;row++)
	{
		for(column=0;column<Temp->column;column++)
		{
			scanf("%lf",&(Temp->num)[row][column]);
		}
	}
	return Temp;
}

void PrintMatrix(Matrix Result)
{
	int rn,cn;
	if(Result==NULL)
	{
		printf("NO RESULT.");
	}
	else
	{
		printf("Result = [");
		for(rn=0;rn<Result->row;rn++)
		{
			if(rn)
			{
				printf("\n          ");
			}
			for(cn=0;cn<Result->column;cn++)
			{
				printf("%8.2lf",(Result->num)[rn][cn]);
			}
		}
		printf(" ]");
	}
	
	
}
