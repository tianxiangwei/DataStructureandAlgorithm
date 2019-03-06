//Barton-Nackmann 技巧或者称 奇异循环模板模式（Curiously Recurring Template Prattern）
#include <iostream>
using namespace std;
/*template<typename T>
class class1
{
public:
    class1(T t):m_val(t){}
    virtual T getVal(){
        cout<<"in class1,val =="<< m_val <<endl;
        return m_val;
    }
private:
    T m_val;
};

class derived: public class1<int>
{
public:
    derived(int i):class1<int>(i){}
    int getVal()
    {
        cout<<"in derived"<<endl;
        return class1<int>::getVal();
    }
};

template<typename T>
class derived2: public class1<T>
{
public:
    derived2(T val):class1<T>(val){}
    T getVal()
    {
        cout<<"in derived2"<<endl;
        return class1<T>::getVal();
    }
};

int main()
{
    class1<int> * pbase = new derived(10);
    pbase->getVal();

    class1<int> * pb2 = new derived2<int>(10);
    pb2->getVal();

    return 0;
}*/

//模板类的虚函数多态,而且派生类可以有两种选择，
//一个实现为普通类，继承的是模板基类的特化类，
//一个就实现模板类（如 derived2）。很明显模板继承类有着普通类不可比拟的灵活性
//下面使用模板来实现多态
template<class derive>
class base
{
public:
    void print()
    {
        cout << "in base print" <<endl;
        derive::print();
    }
    void m_print()
    {
        cout << "in base m_print" << endl;
        downcast()->derive::m_print();
    }
protected:
    inline derive * downcast()
    {
        return static_cast<derive *>(this);
    };
    inline const derive * downcast()const
    {
        return static_cast<const derive *>(this);
    };
};

class der : public base<der>
{
public:
    der(int foo):_foo(foo){}
    static void print()
    {
        cout<<"in der print"<<endl;
    };
    void m_print()
    {
        cout<<"in der member fun m_print"<<endl;
        cout<<"has member foo="<<_foo<<endl;
    }
private:
    int _foo;
};

template<class base>
class der2:public base
{
public:
    static void print()
    {
        cout<<"in der2 print"<<endl;
    };
    void m_print()
    {
        cout<<"in der2 member fun m_print"<<endl;
    }
};

class tmpclass
{
public:
    void test()
    { cout<<"in test"<<endl;}
};

int main(int argc, char* argv[])
{
    //模板实现虚函数多态
    base<der> * pb= new der(100);
    pb->print();
    pb->m_print();

    //动态继承
    der2<tmpclass> d2;
    d2.print();
    d2.m_print();
    d2.test();

    return 0;
}
