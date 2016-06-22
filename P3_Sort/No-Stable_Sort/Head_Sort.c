/*
 * =====================================================================================
 *
 *       Filename:  Head_Sort.c
 *
 *    Description:  Head Sort
 *
 *        Version:  1.0
 *        Created:  06/21/2016 05:40:28 AM
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


void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

//最小堆的父节点比子节点都小，最大堆整好相反

//从i节点开始调整,n为节点总数，从0开始计算 i节点的子结点为2*i+1,2*i+2
void Min_Head_Adjust(int *array,int i,int n)
{
	int j,temp;
	temp=array[i];
	j=2*i+1;
	while(j<n)
	{
		if(j+1<n&&array[j+1]<array[j]) //在左右子节点中找到最小的
			j++;
		if(array[j]>=temp)
			break;
		array[i]=array[j];
		i=j;
		j=2*i+1;
	}
	array[i]=temp;
}

//建立最小堆
void Min_Head_Create(int *array,int n)
{
	int i;
	for(i=n/2-1;i>=0;i--)
		Min_Head_Adjust(array,i,n);
}

//最小堆排序  排序后数组是从大到小的
void Min_Head_Sort(int *array,int n)
{
	int i=0;
	for(i=n-1;i>=1;i--)
	{
		//交换堆顶元素到数组默认，即将最小值放在数组末尾
		swap(&array[i],&array[0]);
		Min_Head_Adjust(array,0,i);
	}
}



//从i节点开始调整,n为节点总数，从0开始计算 i节点的子结点为2*i+1,2*i+2
//构造堆的算法复杂度 T(n)=T(2/3n)+O(1),即O(log(2n))
void Max_Head_Adjust(int *array,int i,int n)
{
	int j,temp;
	temp=array[i];
	j=2*i+1;
	while(j<n)
	{
		if(j+1<n&&array[j+1]>array[j]) //在左右子节点中找到最小的
			j++;
		if(array[j]<=temp)
			break;
		array[i]=array[j];
		i=j;
		j=2*i+1;
	}
	array[i]=temp;
}

//建立最大堆
//构造堆的时间复杂度为O(n),需要n/2*2=n次比较和n/2次交换
void Max_Head_Create(int *array,int n)
{
	int i;
	for(i=n/2-1;i>=0;i--)
		Max_Head_Adjust(array,i,n);
}

//最大堆排序
//算法复杂度为O(n)+(n-1)*O(log(2n))=O(nlog2n)
void Max_Head_Sort(int *array,int n)
{
	int i=0;
	for(i=n-1;i>=1;i--)
	{
		swap(&array[i],&array[0]);
		Max_Head_Adjust(array,0,i);
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

	//Min_Head_Create(a,length);
	//Min_Head_Sort(a,length);

	Max_Head_Create(a,length);
	Max_Head_Sort(a,length);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",a[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
