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

char * test(char *p)
{
	strcpy(p,"txw");
	printf("p:%p\n",p);
	return p;
}
	int
main ( int argc, char *argv[] )
{
	char *str=NULL;
	char temp_str[10];
	char *p;
	memset(temp_str,'\0',sizeof(temp_str));
	getmemory(&str);
	printf("%s\n",str);
	free(str);

	strcpy(temp_str,"mytest");
	p=test(temp_str);
	printf("temp_str:%s %p p:%p\n",temp_str,temp_str,p);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
