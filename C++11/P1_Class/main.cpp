#include <stdio.h>
#include <iostream>
#include "string_test.h"
#include <vector>
void callme1(StringBad &);
void callme2(StringBad);

using namespace std;


void callme1(StringBad &rsb)
{
    printf("rsb:%p &rsb:%p\n", rsb, &rsb);
    cout<<"String passed by reference"<<endl;
    cout<<"rsb:"<<rsb<<endl;
}

void callme2(StringBad sb)
{
    printf("sb:%p &sb:%p\n",sb, &sb);
    cout<<"String passed by value"<<endl;
    cout<<"sb:"<<sb<<endl;
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

    std:;vector<StringBad> _data_buffer;
    std::vector<StringBad *> _circur_buffer;
    cout<<"begin to resize, default constructor"<<endl;
    _data_buffer.resize(1);

    cout<<"\nbegin to push back"<<endl;
    _data_buffer.push_back(StringBad("test node"));
    //create 2 StringBad node

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

    printf("\n StringBad also = StringBad(sports)");
    StringBad also = StringBad(sports);

    printf("\n StringBad *ptest = new StringBad(sports)");
    StringBad * ptest = new StringBad(sports);


    cout<<"\nAssign one object to another"<<endl;
    StringBad knot;
    knot = headline1;
    cout<<"knot:"<<knot<<endl;
    printf("knot:%p &knot:%p\n", knot, &knot);
    cout<<"\nExiting the main"<<endl;
    cout<<"order of deconstructor rever of constructor"<<endl;
    delete ptest;
    return 0;
}