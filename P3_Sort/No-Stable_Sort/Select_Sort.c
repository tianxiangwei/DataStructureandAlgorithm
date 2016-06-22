/*
 * =====================================================================================
 *
 *       Filename:  Select_Sort.c
 *
 *    Description:  :Select Sort
 *
 *        Version:  1.0
 *        Created:  06/21/2016 03:01:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <stdio.h>

//算法复杂度 O(n^2)
void Select_Sort(int array[],int length)
{
	int i,j;
	int temp;
	int min_index=0;
	for(i=0;i<length-1;i++)
	{
		temp=array[i];
		min_index=i;
		for(j=i+1;j<length;j++)
		{
			if(array[j]<temp)
			{
				temp=array[j];
				min_index=j;
			}
		}
		temp=array[i];
		array[i]=array[min_index];
		array[min_index]=temp;
	}
}


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
	int temp[20];
	int partion_index=0;
	int kth_element=0;
	printf("Input the element of Array(0 as input terminated):\n");
	
	do
	{
		scanf("%d",&a[i]);
	}while(a[i++]!=0);

	printf("the array ready to sort:\n");

	length=i-1;
	for(i=0;i<length;i++)
		printf("%d ",a[i]);

	printf("\n");

	Select_Sort(a,length);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",a[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
