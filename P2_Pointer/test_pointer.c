/*
 * =====================================================================================
 *
 *       Filename:  test_sizeof.c
 *
 *    Description:  pointer operation
 *
 *        Version:  1.0
 *        Created:  06/19/2016 12:24:01 AM
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
#include <string.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */

void getmemory(char **p)
{
	*p=(char *)malloc(100);
	strcpy(*p,"hello world");
}
	int
main ( int argc, char *argv[] )
{
	char *str=NULL;
	getmemory(&str);
	printf("%s/n",str);
	free(str);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
