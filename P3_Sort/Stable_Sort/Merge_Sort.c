/*
 * =====================================================================================
 *
 *       Filename:  Merge_Sort.c
 *
 *    Description:  Merge Sort
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

//算法复杂度 O(N*logN)

//first--mid以及mid+1--last的数组元素都是有序的
void  mergearray(int array[],int first,int mid,int last,int temp[])
{
	int i=first,j=mid+1;
	int k=0;
	while(i<=mid&&j<=last)
	{
		if(array[i]<=array[j])
			temp[k++]=array[i++];
		else
			temp[k++]=array[j++];
	}

	while(i<=mid)
		temp[k++]=array[i++];
	while(j<=last)
		temp[k++]=array[j++];

	for(i=0;i<k;i++)
	{
		array[i+first]=temp[i];
		printf("array[%d]:%d ",i+first,array[i+first]);
	}
	printf("\n");

}

void Merge_Sort(int array[],int first,int last,int temp[])
{
	int mid;
	if(first<last)
	{
		mid=(first+last)/2;
		Merge_Sort(array,first,mid-1,temp);//左边有序
		Merge_Sort(array,mid+1,last,temp);//右边有序
		mergearray(array,first,mid,last,temp);//将两个有序队列合并
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

	Merge_Sort(a,0,length-1,temp);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",a[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
