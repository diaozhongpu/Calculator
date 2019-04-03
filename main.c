/*
 * Project 1: Cauculator
 * Coded by DIAO Zhongpu, 2019
 * Submitted in partial fulfillment of the course
 *   C Programming, 2019 Spring
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"normal.h"
#include"poly.h"
#include"matrix.h"


int main()
{
	int mode;
	
	printf("Please choose your mode: 1-normal, 2-polynomial, 3-matrix, else-exit");
	scanf("%d",&mode);
	switch(mode)
	{
		case 1: Normal(); break;
		case 2: Poly(); break;
		case 3: MatrixP(); break;
		default: break;
	}
	
		
	return 0;
}
