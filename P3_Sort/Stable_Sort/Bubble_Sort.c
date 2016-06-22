/*
 * =====================================================================================
 *
 *       Filename:  Bubble_Sort.c
 *
 *    Description:  Bubble Sort
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

//O(n^2)

//内层循环每一次最大数沉地，且通过flag标记可以提前判断退出循环(内层无数据交换，数组已有序)
void Bubble_Sort1(int array[],int length)
{
	int i=0,j=0;
	int flag=0;
	int temp;
	for(i=1;i<length-1;i++)
	{
		flag=0;
		for(j=0;j<length-i;j++)
		{
			if(array[j]>array[j+1])
			{
				flag=1;
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}

		if(flag==0)
			break;

	}
}

void Bubble_Sort(int array[],int length)
{
	int i=0,j=0;
	int temp;
	int n=0;
	for(i=0;i<length-1;i++)
	{
		for(j=i+1;j<length;j++)
		{
			if(array[i]>array[j])
			{
				temp=array[i];
				array[i]=array[j];
				array[j]=temp;
			}
		}

		printf("\n");
		for(n=0;n<length;n++)
			printf("%d ",array[n]);
	}
	printf("\n");
	for(i=0;i<length;i++)
		printf("%d ",array[i]);
	printf("\n");
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

	Bubble_Sort1(a,length);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",a[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
