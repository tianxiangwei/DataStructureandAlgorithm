#include <iostream>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdarg.h>
#include <execinfo.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <vector>
#include <map>
// g++ --std=c++11 thread_int.cpp -lpthread -o thread_int
// ./thread_int

typedef struct Except_frame
{
    jmp_buf env;
    int flag;
    int sig;
    void clear()
    {
       flag = 0;
       bzero(env,sizeof(env));
    }
    bool isDef()
    {
       return flag;
    }
    Except_frame()
    {
      clear();
      sig = 0;
    }
}Except_frame;

std::map<pthread_t, Except_frame*> thread_map;

std::vector<std::thread> thread_vec;
struct ThreadInt {
    ThreadInt() {}
};

void sig_handler(int signum)
{
    pid_t tid = syscall(SYS_gettid);
    pthread_t pid = pthread_self();
    printf("Received signal %d in tid:%d pid:%d\n", signum, tid, (int)pid);
    auto iter = thread_map.find(pid);
    if (iter != thread_map.end()){
        Except_frame *except_frame = thread_map[pid];
        except_frame->sig = signum;
        siglongjmp(except_frame->env,1);
    }
}

void work_func(){
    int count =0;
    while(true){
        if (count == 10) {
            *(int*)0 = 1;
        }
        count++;
        printf("Round :%d\n", count);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void fun(int idx)
{
    pid_t tid = syscall(SYS_gettid);
    pthread_t pid = pthread_self();
    printf("thread_func tid:%d pid:%d\n", tid, (int)pid);
    auto iter = thread_map.find(pid);
    Except_frame *excep_frame = nullptr;
    if (iter != thread_map.end()){
        excep_frame = thread_map[pid];
        printf("Found excep_frame: pid:%d\n",  (int)pid);
    }
    else {
        excep_frame = new Except_frame();
        thread_map[pid] = excep_frame;
        printf("Create excep_frame: pid:%d\n",  (int)pid);
    }
    excep_frame->flag = sigsetjmp(excep_frame->env,1);
    if(!excep_frame->isDef()) 
    { 
      signal(SIGSEGV,sig_handler);
      printf("Signal Register\n");
      work_func();
    }
    else
    {
      excep_frame->clear();
      pid_t tid = syscall(SYS_gettid);
      pthread_t pid = pthread_self();
      printf("Catch Exception:%d tid:%d pid:%lu idx:%d\n", excep_frame->sig, tid, pid, idx);
      thread_vec.push_back(std::thread(fun, 1));
    }
}


int flag = 0;

int main()
{
    pid_t tid = syscall(SYS_gettid);
    printf("main tid:%d\n", tid);
    signal(SIGUSR1, sig_handler);
    signal(SIGSEGV, sig_handler);

    thread_vec.push_back(std::thread(fun, 1));


    while(1){
        sleep(1);
    }

    return 0;
}
