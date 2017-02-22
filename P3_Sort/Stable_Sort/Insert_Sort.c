/*
 * =====================================================================================
 *
 *       Filename:  Insert_Sort.c
 *
 *    Description:  Insert Sort
 *
 *        Version:  1.0
 *        Created:  06/20/2016 08:22:36 PM
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
//折半插入排序
void Binary_Insert_Sort(int array[],int length)
{
	int i=0,j=0;
	int temp;
	int n=0;
	int low,high,mid;
	for(i=1;i<length;i++)
	{
		low=0;
		high=i-1;
		temp=array[i];

		while(low<=high)
		{
			mid=(low+high)/2;
			if(array[mid]>temp)
				high=mid-1;
			else
				low=mid+1;
		}
		for(j=i-1;j>=low;j--)
			array[j+1]=array[j];
		array[low]=temp;
		printf("\n");
		printf("low:%d\n",low);
		for(n=0;n<length;n++)
			printf("%d ",array[n]);
	}
}

void Insert_Sort(int array[],int length)
{
	int i=0,j=0;
	int temp;
	int n=0;
	for(i=1;i<length;i++)
	{
		temp=array[i];
		j=i-1;
		while(j>=0&&array[j]>temp)
		{
			array[j+1]=array[j];
			j--;
		}
		array[j+1]=temp;
		printf("\n");
		printf("***the %d round***\n",i);
		for(n=0;n<length;n++)
			printf("%d ",array[n]);
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

	Insert_Sort(a,length);
	//Binary_Insert_Sort(a,length);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",a[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
