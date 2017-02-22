/*
 * =====================================================================================
 *
 *       Filename:  Bucket_Sort.c
 *
 *    Description:  BUcket Sort
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

//首先定义桶，桶为一个数据容器，每个桶存储一个区间内的数.
//待排序的数据array,元素的最小值不小于0，最大值不超过maxNumber
//假设我们有M个桶，第i个桶Bucket[i]存储i*maxNumber/M至(i+1)maxNumber/M之间的数
//桶排序的一般方法:
//1.扫描序列array,根据每个元素的值所属的区间，放入指定的桶中temp_array(顺序放置)
//2.对桶中的元素进行排序，什么排序算法都可以，例如快速排序
//3.依次收集每个桶中的元素，顺序放置到输出序列中

//算法的时间复杂度
//每个桶中的元素平均个数为N/M，如果每个桶中的元素采用快速排序则每次排序的时间复杂度为
//O(N/Mlog(N/M)).则总的时间复杂度为O(N)+O(M)O(N/Mlog(N/M))=O(N+Nlog(N/M))=O(N+NlogN-NlogM)
//当M接近于N时，桶排序的时间复杂度可近似认为是O(N)的。就是桶越多，时间效率越高，但是空间消耗越大

//将待排序的值作为辅助数组的索引进行标记
//下面的桶排序相当于使用了maxNumber个桶，即变成了计数排序
void Bucket_Sort(int array[],int length,int maxNumber)
{
	int temp_array[maxNumber+1];
	int i,j,count=0;
	
	memset(temp_array,0,(maxNumber+1)*sizeof(int));

	for(i=0;i<length;i++)
	{
		temp_array[array[i]]+=1;
	}
	//temp_array的索引即数组的值 

	for(i=0;i<=maxNumber;i++)
	{
		if(temp_array[i]>0)
		{
			//循环的目的在于处理相同值的情况
			for(j=0;j<temp_array[i];j++)
			{
				array[count]=i;
				count++;
			}
		}
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

	Bucket_Sort(a,length,max);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",a[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
