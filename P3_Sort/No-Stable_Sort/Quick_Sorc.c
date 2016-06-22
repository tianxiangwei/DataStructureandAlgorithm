/*
 * =====================================================================================
 *
 *       Filename:  Quick_Sorc.c
 *
 *    Description:  Quick Sort
 *
 *        Version:  1.0
 *        Created:  06/21/2016 12:29:48 AM
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

int random_partition(int *array,int begin,int last)
{
	int len,i,j,index;
	len=last-begin+1;
	srand(time(NULL));
	index=begin+rand()%len;
	printf("index:%d\n",index);
	swap(array+index,array+last);
	i=begin;
	for(j=begin;j<last;j++)
	{
		if(array[j]<array[last])
		{
			swap(array+i,array+j);
			i++;
		}
	}
	swap(array+i,array+last);
	return i;
}

int find_kth_min(int *array,int begin,int last,int k)
{
	int partion_index,n;
	if(begin==last)
		return array[begin];
	partion_index=random_partition(array,begin,last);
	n=partion_index-begin+1;
	if(n==k)
		return array[partion_index];
	else if(k>n)
		find_kth_min(array,partion_index+1,last,k-n);
	else
		find_kth_min(array,begin,partion_index-1,k);
}

void Quick_Sort(int array[],int left,int right)
{
	int lbase,rbase;
	int temp;
	int i=0;
	if(left<right)
	{
		lbase=left;
		rbase=right;
		while(lbase<rbase)
		{
			for(lbase=lbase+1;lbase<right;lbase++)
				if(array[lbase]>array[left])
					break;
			for(;rbase>left;rbase--)
				if(array[rbase]<array[left])
					break;
			if(lbase<rbase)
			{
				temp=array[lbase];
				array[lbase]=array[rbase];
				array[rbase]=temp;
			}
		}
		temp=array[left];
		array[left]=array[rbase];
		array[rbase]=temp;
		for(i=left;i<=right;i++)
			printf("array[%d]:%d ",i,array[i]);
		printf("\n");
		Quick_Sort(array,left,rbase-1);
		Quick_Sort(array,rbase+1,right);
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

	kth_element=find_kth_min(a,0,length-1,3);
	printf("kth_element:%d\n",kth_element);

	//Quick_Sort(a,0,length-1);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",a[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
