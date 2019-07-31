#include <iostream>
#include <stdio.h>
using namespace std;

class Father
{
public:
    Father(){cout<<"contructor Father!"<<endl;};
    virtual ~Father(){
        cout<<"destructor Father!"<<endl;
        printf("ptr:%p\n", ptr);
        delete[] ptr;
        ptr = 0;
    };
public:
    char *ptr;
};

class Son:public Father
{
public:
    Son(){cout<<"contructor Son!"<<endl;};
    ~Son(){cout<<"destructor Son!"<<endl;};
};

int main()
{
    Father *pfather1=new Son;
    pfather1->ptr = new char[10];
    
    Father *pfather2=new Son;
    pfather2->ptr = new char[20];
    
    delete pfather1;
    delete pfather2;

    return 0;
}
