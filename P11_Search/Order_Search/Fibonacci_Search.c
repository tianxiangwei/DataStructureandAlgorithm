/*
 * =====================================================================================
 *
 *       Filename:  Fibonacci_Search.c
 *
 *    Description: 非波那契查找 
 *
 *        Version:  1.0
 *        Created:  03/19/2017 04:14:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include 	<stdio.h>

#define MAXN 20

void Fibonacci(int *f)
{
	int i;
	f[0]=1;
	f[1]=1;
	for(i=2;i<MAXN;++i)
		f[i]=f[i-1]+f[i-2];
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Fibonacci_Search
 *  Description:  
 * =====================================================================================
 */
int Fibonacci_Search (int array[],int length,int value)
{
	int i,low=0,high=length-1;
	int mid=0;
	int k=0;
	int F[MAXN];
	Fibonacci(F);
	while(length>F[k]-1)
		k++;
	for(i=length;i<F[k]-1;i++)
		array[i]=array[high];

	while(low<=high)
	{
		mid=low+F[k-1]-1;
		if(array[mid]>value)
		{
			high=mid-1;
			k=k-1;
		}
		else if(array[mid]<value)
		{
			low=mid+1;
			k=k-2;
		}
		else
		{
			if(mid<=high)
				return mid;
			else
				return -1;
		}
	}
	return -1;
}		/* -----  end of function Fibonacci_Search  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int i=0;
	int a[MAXN];
	int length=0;
	int value;
	int index;
	printf("Input the element of Array(0 as input terminated):\n");
	
	do
	{
		scanf("%d",&a[i]);
	}while(a[i++]!=0);

	printf("the array ready to search:\n");

	length=i-1;
	for(i=0;i<length;i++)
		printf("%d ",a[i]);

	printf("\n");

	printf("Input the value to search:\n");
	scanf("%d",&value);

	index=Fibonacci_Search(a,length,value);

	if(index>=0)
		printf("\nthe value on index:%d\n",index);
	else
		printf("\ncan't find the value\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

