// test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define  D_Out(x) \
cout << (x);\
ofstream outfile;\
outfile.open("testDestructor.txt", std::ofstream::app);\
outfile << (x) << endl;\
outfile.close();


class  A
{
public:
     A();
    ~ A();

private:

};

 A:: A()
{
     D_Out("class A constructor")
}

 A::~ A()
{
     D_Out("class A destructor")
}

 class B
 {
 public:
     B();
     ~B();

 private:

 };

 B::B()
 {
     D_Out("class B constructor")
 }

 B::~B()
 {
     D_Out("class B destructor")
 }

 class C 
 {
 public:
     C ();
     ~C ();

 private:

 };

 C ::C ()
 {
     D_Out("class C constructor")
 }

 C ::~C ()
 {
     D_Out("class C destructor")
 }

 class D
 {
 public:
     D();
     ~D();

 private:

 };

 D::D()
 {
     D_Out("class D constructor")
 }

 D::~D()
 {
     D_Out("class D destructor")
 }

 class E
 {
 public:
     E();
     ~E();

 private:

 };

 E::E()
 {
     D_Out("class E constructor")
 }

 E::~E()
 {
     D_Out("class E destructor")
 }


 static E e2;
 C c;
 void test_func(){
    std::cout << "test_func begin" << std::endl;
    static D d;
    std::cout << "test_func exit" << std::endl;
 }
int main()
{
    A *a = new A();
    B b;

    test_func();
    delete a;
    a = NULL;
    return 0;
}
