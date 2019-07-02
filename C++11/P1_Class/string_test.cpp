#include <stdio.h>
#include <cstring>
#include "string_test.h"
using namespace std;

int StringBad::num_strings = 0;

StringBad::StringBad(const char *s){
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings++;
    printf("this:%p ",this);
    /*for(int i=0; i<12; i++){
        printf("test_array[%d]:%d\n", i, test_array[i]);
    }*/
    cout <<num_strings<<":"<<str<<"-->object created\n";
}

StringBad::StringBad()
{
    len = 4;
    str =new char[4];
    std::strcpy(str, "C++");
    num_strings++;
    printf("this:%p ",this);
    cout<<num_strings<<":"<<str<<" default object created\n";
}

StringBad::~StringBad()
{
    printf("deconstructor this:%p ",this);
    cout<<str<<"-->object deleted\n";
    --num_strings;
    cout<<num_strings<<" left\n";
    delete [] str;
}

//复制构造函数
StringBad::StringBad(const StringBad & st)
{
    cout<<"copy construnctor"<<std::endl;
    printf("st:%p &st:%p\n", st, &st);
    num_strings++;
    len=st.len;
    str=new char[len+1];
    std::strcpy(str,st.str);
    test=st.test;
    printf("this:%p ",this);
    cout<<num_strings<<":"<<str<<"-->object created\n";
}

//ANSI C允许结构赋值,而C++允许类对象赋值，这是通过自动为类重载赋值运算符实现的
StringBad & StringBad::operator=(const StringBad & st){
    if(this==&st)
        return *this;
    printf("= operator-->this:%p st:%p\n",this,st);
    delete []str;
    len = st.len;
    str = new char[len+1];
    std::strcpy(str,st.str);
    test=st.test;
    return *this;
}

bool operator<(const StringBad &st1, const StringBad &st2)
{
    return (std::strcmp(st1.str, st2.str)<0);
}

bool operator>(const StringBad &st1, const StringBad &st2)
{
    return st2<st1;
}

bool operator==(const StringBad &st1, const StringBad &st2){
    return (std::strcmp(st1.str,st2.str)==0);
}

std::ostream & operator<<(std::ostream &os, const StringBad &st){
    //cout<<"operator \<\<\n";
    os << st.str;
    return os;
}

istream & operator>>(istream &is, StringBad &st)
{
    char temp[StringBad::CINLIM];
    is.get(temp,StringBad::CINLIM);
    printf(">> st:%p\n",st);
    if(is)
        st=temp;
    while(is&&is.get()!='\n')
        continue;
    return is;
}

void * StringBad::alloc_test()
{
    test = new char[100];
}
