/*
* cauculator.c
*
*
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
		case 3: Matrix(); break;
		default: break;
	}
	
		
	return 0;
}
