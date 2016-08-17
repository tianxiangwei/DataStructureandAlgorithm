/*
 * =====================================================================================
 *
 *       Filename:  Z_Process.c
 *
 *    Description:  避免僵尸进程的两种方法
 *
 *        Version:  1.0
 *        Created:  08/17/2016 07:53:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static void sig_child(int signo);
int double_fork();

/*
 * 孤儿进程:一个父进程退出，而它的一个或者多个子进程还在运行，那么这些子进程成为孤儿进程，它们由init进程(pid=1)所收养，
 * 并由init进程对它们完成状态收集工作。
 * 僵尸进程:一个进程通过fork创建子进程，如果子进程退出，而父进程并没有调用wait或waitpid获取子进程的状态信息，
 * 那么子进程的进程状态描述符仍然保留在系统中，这种进程称之为僵尸进程。
 * */

int main()
{
	/*  pid_t pid;
	
	signal(SIGCHLD,sig_child);
	
	pid=fork();
	if(pid<0)
	{
		perror("fork error!");
		exit(1);
	}
	else if(pid==0)
	{
		printf("I'm child process(pid:%d ppid:%d),i'm exiting\n",getpid(),getppid());
		exit(0);
	}
	printf("i'm father process(pid:%d ppid:%d),i will sleep two seconds\n",getpid(),getppid());
	sleep(2);
	system("ps -o pid,ppid,state,command");
	printf("father process is exiting\n");*/

	double_fork();
}

//信号机制
static void sig_child(int signo)
{
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("child pid %d terminated\n",pid);
}

//fork两次，使子进程成为孤儿进程

int double_fork()
{
	
	pid_t pid;
	
	pid=fork();
	if(pid<0)
	{
		perror("fork error!");
		exit(1);
	}
	else if(pid==0)
	{
		pid=fork();
		if(pid<0)
		{
			perror("second fork error!");
			exit(1);
		}
		else if(pid==0)
		{
			sleep(3);
			printf("the second child process(pid:%d ppid:%d)\n",getpid(),getppid());
			exit(0);
		}
		else
		{
			printf("the first child process(pid:%d ppid:%d)\n",getpid(),getppid());
			exit(0);
		}
		printf("I'm child process(pid:%d ppid:%d),i'm exiting\n",getpid(),getppid());
		exit(0);
	}

	printf("the master process(pid:%d ppid:%d)\n",getpid(),getppid());

	if((pid=waitpid(pid,NULL,0))!=pid)
	{
		perror("waitpid error\n");
		exit(1);
	}
	exit(0);
}



