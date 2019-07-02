#include <stdio.h>
#include <iostream>
#include "string_test.h"
#include <vector>
#include <unistd.h>
void callme1(StringBad &);
void callme2(StringBad);

using namespace std;


void callme1(StringBad &rsb)
{
    printf("rsb:%p &rsb:%p\n", rsb, &rsb);
    cout<<"String passed by reference"<<endl;
    cout<<"rsb:"<<rsb<<endl;
}

//按值传递对象涉及到生成临时拷贝,即调用复制构造函数，然后调用析构函数，调用这些函数需要时间
//复制大型对象比传递引用花费的时间要多得多
void callme2(StringBad sb)
{
    printf("sb:%p &sb:%p\n",sb, &sb);
    cout<<"String passed by value"<<endl;
    cout<<"sb:"<<sb<<endl;
}


StringBad callme3(StringBad sb)
{
    //按值传递参数调用拷贝构造函数
    printf("sb:%p &sb:%p\n",sb, &sb);
    cout<<"String passed by value"<<endl;
    cout<<"sb:"<<sb<<endl;
    //return StringBad(sb);
    return sb;
}

StringBad &callme4(StringBad &sb)
{
    printf("sb:%p &sb:%p\n",sb, &sb);
    cout<<"String passed by reference"<<endl;
    cout<<"sb:"<<sb<<endl;
    return sb;
}

int main()
{
    StringBad headline1("Celery Stalks at Midnight");
    StringBad headline2("Lettuce Pre");
    StringBad sports("Spinach Leaves Bowl for Dollars");

    cout<<""<<endl;
    StringBad name;
    std::cin>>name;
    cout<<name<<endl;
    printf("name:%p\n",name);
    cout<<""<<endl;
    int test_value = 10;
    int test_value1 = 20;
    printf("stack adress: test_value:%p test_value:%p\n", &test_value, &test_value1);

    int *test_array = new int(3) ;
    int *test_array1 = (int *)malloc(3*sizeof(int));
    printf("heap adress: test_arrary:%p test_array1:%p\n", test_array, test_array1);
    cout << "vector Test:" <<endl; 
    std:;vector<StringBad> _data_buffer;
    std::vector<StringBad *> _circur_buffer;
    //cout<<"begin to resize, default constructor"<<endl;
    //_data_buffer.resize(1);

    _data_buffer.clear();
    //事先给vector分配好内存，不会在第二次push_back时对第一次push_back的值进行拷贝构造
    _data_buffer.reserve(2);
    cout<<"\nbegin to push back"<<endl;
    //伴随栈上临时对象的创建，以及vector上堆上空间的分配，同时调用拷贝构造函数将临时对象赋值给对上开辟的对象，栈对象自动析构
    _data_buffer.push_back(StringBad("test1 node"));
    _data_buffer.push_back(StringBad("test2 node"));
    printf("capacity:%lu size:%lu\n", _data_buffer.capacity(), _data_buffer.size());
    //create 2 StringBad node

    cout<<""<<endl;
    cout<<"vecotr back"<<endl;
    StringBad node1 = _data_buffer.back();
    //_data_buffer.back();
    //apollo_circur_buffer.push_back(&_data_buffer.back());
    //printf("_circur_buffer[0]:%p\n", _circur_buffer[0]);
    
    cout<<"\nclear vector"<<endl;
    _data_buffer.clear();

    cout<<"\nbegin to emplace back"<<endl;
    // _data_buffer.emplace_back(StringBad("emplace node"));
    _data_buffer.emplace_back("emplace node");

    cout<<""<<endl;
    StringBad *test_node=&_data_buffer.back();
    printf("test_node:%p\n",test_node);

    cout<<""<<endl;
    _circur_buffer.push_back(&_data_buffer.back());
    printf("_circur_buffer[0]:%p\n", _circur_buffer[0]);

    cout<<""<<endl;
    cout<<"headline1:"<<headline1<<endl;
    cout<<"headlin2:"<<headline2<<endl;
    cout<<"sports:"<<sports<<endl;

    cout<<""<<endl;
    cout<<"====callme1===="<<endl;

    printf("headline1:%p &headline1:%p\n", headline1, &headline1); 

    callme1(headline1);

    cout<<"headline1:"<<headline1<<endl;

    cout<<""<<endl;
    cout<<"====callme2===="<<endl;
    printf("headline2:%p &headline2:%p\n", headline2, &headline2); 
    callme2(headline2);
    cout<<"headline2:"<<headline2<<endl;

    cout<<""<<endl;

    printf("sports:%p &sports:%p\n", sports, &sports);
    
    cout<<"4 deplare to call copy constructor"<<endl;

    printf("\n StringBad ditto(sports)\n");
    sports.alloc_test();
    StringBad ditto(sports);
    printf("sports.test:%p ditto.test:%p\n", sports.test, ditto.test);

    printf("\n StringBad sailor = sports \n");
    StringBad sailor = sports;

    printf("\n StringBad also = StringBad(sports)\n");
    StringBad also = StringBad(sports);

    printf("\n StringBad *ptest = new StringBad(sports)");
    StringBad * ptest = new StringBad(sports);


    cout<<"\nAssign one object to another"<<endl;
    StringBad knot;
    knot = headline1;
    cout<<"knot:"<<knot<<endl;
    printf("knot:%p &knot:%p\n", knot, &knot);

    cout<<endl;
    StringBad testnode1;
    //调用转换构造函数生成对象 StringBad(const char *s)
    testnode1 = "this is test";
    printf("test_node1:%p\n",testnode1);

    //函数参数按值传递
    cout<<endl;
    cout<<"callme3"<<endl;
    StringBad testnode2 = callme3(testnode1);
    printf("testnode2:%p\n", testnode2);
    //函数参数按引用传递
    cout<<endl;
    StringBad &testnode3 = callme4(testnode1);
    printf("testnode3:%p\n", testnode3);
    
    cout<<"\nExiting the main"<<endl;
    cout<<"order of deconstructor rever of constructor"<<endl;
    delete ptest;
    while(1){
        sleep(1);
    }
}
