/*
 * =====================================================================================
 *
 *       Filename:  RedBlackTree_Search.c
 *
 *    Description:  红黑数查找 
 *
 *        Version:  1.0
 *        Created:  03/19/2017 04:41:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


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
