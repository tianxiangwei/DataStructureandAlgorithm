/*
 * =====================================================================================
 *
 *       Filename:  signal_test.c
 *
 *    Description:  signal test
 *
 *        Version:  1.0
 *        Created:  08/19/2016 05:09:30 PM
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
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
void deal()
{
	printf("deal signal--SIG_INIT\n");
}

void handler(int sig)
{
	if(sig==SIGINT)
		printf("SIGINT sig\n");
	else if(sig==SIGQUIT)
		printf("SIGQUIT sig\n");
	else if(sig==SIGUSR1)
		printf("SIGUSR1 sig\n");
	else
		printf("unkown sig:%d\n",sig);
}
/*
 * 任何信号都可以唤醒pause
 * */
void main()
{
	/*  int ret=0;
	printf("process start\n");
	signal(SIGINT,deal);
	ret=pause();
	printf("ret:%d %s\n",ret,strerror(errno));
	printf("process end\n");*/



	sigset_t new,old,wait;
	struct sigaction act;
	act.sa_handler=handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGINT,&act,0);
	sigaction(SIGQUIT,&act,0);
	sigaction(SIGUSR1,&act,0);
	sigemptyset(&new);
	sigaddset(&new,SIGINT);
	sigemptyset(&wait);
	//sigaddset(&wait,SIGUSR1);
	sigprocmask(SIG_BLOCK,&new,&old);

	if(sigsuspend(&wait)!=-1)
		printf("sigsuspend error\n");
	/*sigsuspend unlock所有信号，并且这是个原子操作，处理完一个信号后又阻塞之前的信号*/
	printf("after sigsuspend\n");
	//sigprocmask(SIG_SETMASK,&old,NULL);
	pause();
	return ;
}
