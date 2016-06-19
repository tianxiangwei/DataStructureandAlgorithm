/*
 * =====================================================================================
 *
 *       Filename:  test_sizeof.c
 *
 *    Description:  data alignment and sizeof
 *
 *        Version:  1.0
 *        Created:  06/19/2016 12:24:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include <stdio.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */

typedef union
{
	long i;
	int k[5];
	char c;
}DATE;

struct data
{
	int cat;
	DATE cow;
	double dog;
};

struct name1
{
	char str;
	short x;
	int num;
};
struct name2
{
	char str;
	int num;
	short x;
};

#define SQUARE(a) ((a)*(a))
	int
main ( int argc, char *argv[] )
{
	DATE max;
	struct data too;
	int a=5;
	int b;
	b=SQUARE(a++);
	printf("b:%d\n",b);
	printf("sizeof(max):%d,sizeof(struct data):%d sizeof(too):%d\n",\
			sizeof(max),sizeof(struct data),sizeof(too));
	printf("sizeof(name1):%d sizeof(name2):%d\n",sizeof(struct name1),sizeof(struct name2));
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
