/*
 * =====================================================================================
 *
 *       Filename:  Insert_Search.c
 *
 *    Description:  Insert Value Search
 *
 *        Version:  1.0
 *        Created:  03/19/2017 03:37:12 PM
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

//对于表比较大，而关键字分布又比较均匀的查找表来说，插值查找算法的平均性能比折半查找要好的多，反之
//如果数组中的值分布不均匀，插值查找的效果反而变差
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Insert_Search
 *  Description:  
 * =====================================================================================
 */
int Insert_Search (int array[],int length,int value)
{
	int mid;
	int low=0;
	int high=length-1;

	if(value<array[low]||value>array[high])
		return -1;
	while(low<=high)
	{
		if(array[high]==array[low])
		{
			if(value==array[high])
				return high;
			else
				return -1;
		}
		mid=low+(value-array[low])/(array[high]-array[low]);
		if(array[mid]>value)
			high=mid-1;
		else if(array[mid]<value)
			low=mid+1;
		else 
			return mid;
	}
	return -1;
}		/* -----  end of function Insert_Search  ----- */
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

	index=Insert_Search(a,length,value);

	if(index>=0)
		printf("\nthe value on index:%d\n",index);
	else
		printf("\ncan't find the value\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
