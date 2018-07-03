/// @file stack_test.cpp
/// @brief stack grew direction
/// @author tianxiangwei@baidu.com
/// @version 1.0
/// @date 2018-03-30
#include <iostream>
#include <vector>
//使用test一个函数无法确定栈的生长方向
//函数的调用过程中，函数的相关信息会一起送入栈，这些信息包括了参数，返回地质
//和局部变量，通常这些与函数调用相关的东西叫栈帧，在一个栈帧里这些东西的相对
//顺序是由编译器决定的，所以仅仅在一个栈帧内作比较，都会都编译器有依赖，而无法确定栈的生长方向。
//因此find_stack_direction使用两个栈帧的东西进行比较就可以确定栈的方向

//栈从高地址向低地址增长，堆正好相反。
//这种方案与虚拟地址空间的分配规则有关，每个可执行的c程序，从低地址到高地址依次是:text,data,bss,堆，栈,环境参数变量
//其中堆和栈之间有很大的地址空间空闲，在需要分配空间的时候，堆向上涨，栈向下涨
//这样设计可以使得堆和栈能够充分利用空闲的地址空间

int test1(int *p)
{
    int c=0;
    int *c_p=nullptr;
    std::cout<<"p:"<<p<<" c:"<<&c<<std::endl;
    c_p=&c;
    if(c_p<p)
        std::cout<<("stack grew downward")<<std::endl;
    else
        std::cout<<"stack grew upward"<<std::endl;
}

int test(int x,int y)
{
    int a=0;
    int b=0;
    printf("x:%d %p y:%d %p\n",x,&x,y,&y);
    printf("a:%d %p b:%d %p\n",a,&a,b,&b);
    test1(&a);
    return 0;

}

int stack_dir=0;

static void find_stack_direction (void)  {
    static char   *addr = NULL;   /* address of first
                                     `dummy', once known */
    char     dummy;          /* to get stack address */

    if (addr == NULL)
    {                           /* initial entry */
        addr = &dummy;

        find_stack_direction ();  /* recurse once */
    }
    else                          /* second entry */
        if (&dummy > addr)
            stack_dir = 1;            /* stack grew upward */
        else
            stack_dir = -1;           /* stack grew downward */
}
int main()
{
    using namespace std;
    double a0[4] = {1.2, 2.4, 3.6, 4.8};
    double a1[4] = {1.2, 2.4, 3.6, 4.8};
    vector<double> a2(4);
    vector<double> a3(4);
    
    a2[0] = 1.0/3.0;
    a2[1] = 1.0/5.0;
    a2[2] = 1.0/7.0;
    a2[3] = 1.0/9.0;
    a3[0] = 1.0/3.0;
    a3[1] = 1.0/5.0;
    a3[2] = 1.0/7.0;
    a3[3] = 1.0/9.0;
    cout << "a0[2]: " << a0[2] << " at " << &a0[2] << endl;
    cout << "a1[2]: " << a1[2] << " at " << &a1[2] << endl;
    cout << "a1[3]: " << a1[3] << " at " << &a1[3] << endl;
    cout << "a2[2]: " << a2[2] << " at " << &a2[2] << endl;
    cout << "a2[3]: " << a2[3] << " at " << &a2[3] << endl;
    cout << "a3[2]: " << a3[2] << " at " << &a3[2] << endl;
    cout << "a3[3]: " << a3[3] << " at " << &a3[3] << endl;
    
    test(10,20);

    find_stack_direction();
    if(stack_dir==1)
        printf("stack grew upward\n");
    else
        printf("stack grew downward\n");
    return 0;
}

