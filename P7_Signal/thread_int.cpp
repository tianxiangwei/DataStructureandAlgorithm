#include <iostream>
#include <thread>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <vector>
// g++ --std=c++11 thread_int.cpp -lpthread -o thread_int
// ./thread_int

std::vector<std::thread> thread_vec;
struct ThreadInt {
    ThreadInt() {}
};

void sig_handler(int signum)
{
    pid_t tid = syscall(SYS_gettid);
    pthread_t pid = pthread_self();
    printf("Received signal %d in tid:%d pid:%d\n", signum, tid, (int)pid);
    throw ThreadInt();
}

void work_func(int count){
    if (count == 10) {
        *(int*)0 = 1;
    }
}

void fun(int idx)
{
    int s = 0;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGSEGV);
    s = pthread_sigmask(SIG_UNBLOCK, &set, NULL);
    if (s != 0)
        printf("pthread sigmask failed");
    signal(SIGSEGV, sig_handler);
    int count =0;
    while(true){
        try {
            work_func(count);
        } catch (ThreadInt& i) {
            pid_t tid = syscall(SYS_gettid);
            pthread_t pid = pthread_self();
            printf("catch tid:%d pid:%d\n", tid, (int)pid);
            printf("catch segmentfault");
            //thread_vec.push_back(std::thread(fun, 1));
            break;
        }
        /*if (count == 10 && idx == 1) {
                *(int*)0 = 1;
        }*/
        std::cout << "in fun: " << idx << ", " << count++<< std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


int flag = 0;

int main()
{
    pid_t tid = syscall(SYS_gettid);
    printf("main tid:%d\n", tid);
    signal(SIGUSR1, sig_handler);
    signal(SIGSEGV, sig_handler);

    sleep(3);
   
    //thread_vec.push_back(std::thread(fun, 1));
   auto th1 = std::thread([](){
            pid_t tid = syscall(SYS_gettid);
            printf("thread1 tid:%d\n", tid);
            fun(1);
    });
   /* auto th1 = std::thread([](){
        try {
            pid_t tid = syscall(SYS_gettid);
            printf("thread1 tid:%d\n", tid);
            fun(1);
        } catch (ThreadInt& i) {
            pid_t tid = syscall(SYS_gettid);
            pthread_t pid = pthread_self();
            printf("Catch tid:%d pid:%d\n", tid, (int)pid);
            //signal(SIGSEGV, sig_handler);
            thread_vec.push_back(std::thread(fun, 1));
            //flag = 1;
        }
    });*/
    while(!flag){
        sleep(1);
    }
    /*auto th2 = std::thread([](){
        try {
            pid_t tid = syscall(SYS_gettid);
            printf("thread2 tid:%d\n", tid);
            fun(1);
        } catch (ThreadInt i) {
            std::cout << "thread 2 interrupt" << std::endl;
            pid_t tid = syscall(SYS_gettid);
            pthread_t pid = pthread_self();
            printf("Catch tid:%d pid:%d\n", tid, (int)pid);
        }
    });*/


    while(1){
        sleep(1);
    }

    bool stop = false;
    while (!stop) {
        char c;
        std::cin >> c;
        std::cout << c << std::endl;
        switch (c) {
            case 'q':
                stop = true;
                break;
            case '1':
                //pthread_kill(th1.native_handle(), SIGUSR1);
                break;
            case '2':
                //pthread_kill(th2.native_handle(), SIGUSR1);
                break;
        }
    }
    std::cout << "main end" << std::endl;
    //th1.join();
    //th2.join();
    return 0;
}
