/*
 * =====================================================================================
 *
 *       Filename:  Couting_Sort.c
 *
 *    Description:  Couting Sort
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
#include <string.h>

//假定有一个待排序的数组array,其中元素的最小值不小于0，最大值不大于maxN.
//建立一个长度为maxNumber的线性表temp_array,用来记录不大于每个值的元素的个数
//算法思路如下:
//1.扫描待排序序列array,以array中的值为索引把出现的个数记录进temp_array中，此时temp_array[i]可以表示array中值为i的元素的个数
//2.对于temp_array从头开始累加，使temp_array[i]表示array中值不大于i的元素的个数
//3.按照统计出的值输出结果

//时间复杂度 O(n+k),n为数组长度即length,k为最大值即maxNumber
void Couting_Sort(int array[],int array_res[],int length,int maxNumber)
{
	int temp_array[maxNumber+1];
	int Order[maxNumber+1];
	int i,j,count=0;
	
	memset(temp_array,0,(maxNumber+1)*sizeof(int));

	for(i=0;i<length;i++)
	{
		temp_array[array[i]]+=1;
	}

	for(i=1;i<=maxNumber;i++)
	{
		temp_array[i]+=temp_array[i-1];//统计不大与i的元素的个数
	}

	for(i=length-1;i>=0;i--)
	{
		array_res[temp_array[array[i]]-1]=array[i];
		//Order的索引即新数组的索引，其值代表原数组元素的索引位置
		Order[temp_array[array[i]]-1]=i;
		temp_array[array[i]]--;
	}

	printf("the order of array:\n");
	for(i=0;i<length;i++)
	{
		printf("%d ",Order[i]);
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
	int b[20];
	int length=0;
	int max=-1;
	printf("Input the element of Array(0 as input terminated):\n");
	
	do
	{
		scanf("%d",&a[i]);
	}while(a[i++]!=0);

	printf("the array ready to sort:\n");

	length=i-1;
	for(i=0;i<length;i++)
	{
		if(a[i]>max)
			max=a[i];
		printf("%d ",a[i]);
	}

	printf("\n");

	Couting_Sort(a,b,length,max);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",b[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
