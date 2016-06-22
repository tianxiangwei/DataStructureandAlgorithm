/*
 * =====================================================================================
 *
 *       Filename:  Shell_Sort.c
 *
 *    Description:  Shell Sort
 *
 *        Version:  1.0
 *        Created:  06/21/2016 08:45:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//希尔排序原始实现  变步长的插入排序
//时间复杂度高于O(n^2)
void Shell_Sort(int *array,int length)
{
	int gap,temp,i,j,step;
	for(gap=length/2;gap>0;gap=gap/2)
	{
		for(step=0;step<gap;step++)
		{
			for(i=step+gap;i<length;i+=gap)
			{
				if(array[i]<array[i-gap])
				{
					temp=array[i];
					j=i-gap;
					while(j>=0&&array[j]>temp)
					{
						array[j+gap]=array[j];
						j-=gap;
					}
					array[j+gap]=temp;
				}
			}

		}

		printf("gap:%d\n",gap);
		for(i=0;i<length;i++)
			printf("%d ",array[i]);
		printf("\n");
	}

}

//希尔排序改进
void Shell_Sort1(int *array,int length)
{
	int gap,temp,i,j;
	for(gap=length/2;gap>0;gap/2)
	{
		for(i=gap;i<length;i++)
		{
			if(array[i]<array[i-gap])
			{
				temp=array[i];
				j=i-gap;
				while(j>=0&&array[j]>temp)
				{
					array[j+gap]=array[j];
					j-=gap;
				}
				array[j+gap]=temp;
			}
		}

		printf("gap:%d\n",gap);
		for(i=0;i<length;i++)
			printf("%d ",array[i]);
		printf("\n");
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

	Shell_Sort(a,length);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",a[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
