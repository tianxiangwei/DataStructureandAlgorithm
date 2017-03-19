/*
 * =====================================================================================
 *
 *       Filename:  Binary_Search.c
 *
 *    Description:  Binray Search
 *
 *        Version:  1.0
 *        Created:  03/19/2017 03:10:33 PM
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
 *         Name:  Binary_Search
 *  Description:  
 * =====================================================================================
 */
int Binary_Search (int array[],int length,int value)
{
	int mid;
	int left=0;
	int right=length-1;
	while(left<=right)
	{
		mid=(left+right)/2;
		if(array[mid]>value)
			right=mid-1;
		else if(array[mid]<value)
			left=mid+1;
		else
			return mid;
	}
	return -1;
}		/* -----  end of function Binary_Search  ----- */
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
	int a[20];
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

	index=Binary_Search(a,length,value);

	if(index>=0)
		printf("\nthe value on index:%d\n",index);
	else
		printf("\ncan't find the value\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
