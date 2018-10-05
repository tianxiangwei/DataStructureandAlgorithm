//C++类型转换分为两种:
//隐式类型转换
//显示类型转换

#include <iostream>
#include <string>
class Base
{
    public:
    int m_iNum;
    virtual void foo();
};

class Derived:public Base
{
    public:
    char *m_szName[100];
};

void func(Base *pb)
{
   // Derived *pd1 = static_cast<Derived *>(pb);
    //Derived *pd2 = dynamic_cast<Derived *>(pb);
}
//在上面的代码段中:
//如果pb实际指向一个Derived类型的对象，pd1和pd2是一样的，并且对这两个指针执行Derived类型的任何操作都是安全的；
//如果pb实际指向的是一个Base类型的对象，那么pd1将是一个指向该对象的指针，
//对它进行Derived类型的操作将是不安全的（如访问m_szName），而pd2将是一个空指针(即0，因为dynamic_cast失败)。
//另外要注意：Base要有虚函数，否则会编译出错；static_cast则没有这个限制。
//这是由于运行时类型检查需要运行时类型信息，而这个信息存储在类的虚函数表中，只有定义了虚函数的类才有虚函数表，
//没有定义虚函数的类是没有虚函数表的。
    
//dynamic_cast支持的交叉转换
class Base1
{
    public:
    int m_iNum;
    virtual void f(){}
};


class Derived1 : public Base1
{

};

class Derived2 : public Base1
{

};

void foo1()
{
    Derived1 *pd1 = new Derived1;
    pd1->m_iNum = 100;
    //Derived2 *pd2 = static_cast<Derived2 *>(pd1); //compile error
    Derived2 *pd2 = dynamic_cast<Derived2 *>(pd1); //pd2 is NULL
    delete pd1;
}
//在函数foo中，使用static_cast进行转换是不被允许的，将在编译时出错；而使用 dynamic_cast的转换则是允许的，结果是空指针
    
class B
{
    public:
    B(){}
    int m_iNum;
};

void foo2(){

    const B b1;

    //b1.m_iNum = 100; //comile error

    B *b2 = const_cast<B*>(&b1);

    b2->m_iNum = 200; //fine
}
//上面的代码编译时会报错，因为b1是一个常量对象，不能对它进行改变；
//使用const_cast把它转换成一个常量对象，就可以对它的数据成员任意改变。
using namespace std;
int main()
{

    //一、 隐式类型转换
    //1.算术转换  最宽数据类型为转换类型
    int ival =3 ;
    double dval =4.5;
    double sval = ival + dval; //ivale被提升成double
    //2.一种类型表达式赋值给另一种类型对象 目标类型是被赋值对象的类型
    int *pi=0; //0被转化为int类型
    ival = dval; //double-->int
    //3. 将一个表达式作为实参传递给函数调用，此时形参和实参类型不一致 ：目标转换类型为形参的类型
    //extern double squt(double);
    //sqrt(2); //2 from int to double
    //4. 从一个函数返回一个表达式 表达式类型与返回类型不一致 ：目标转换类型为函数的返回类型 
    /*double diffrence(int ival1, int ival2)
    {
        return ival1 + ival2; //int -->double
    }*/

    //二. 显式类型转换--强制类型转换
    //static_cast<tyep_id> (expression)
    //该运算符将expression转换为type-id类型，但没有运行时类型检查来保证转换的安全性
    //适用场景如下：
    //1.用于类层次结构中基类和子类之间指针和引用的转换，进行上行转换(把子类的指针或者引用转换成基类表示)是安全的，
    //进行下行转换(把基类指针或者引用转换成子类指针或者引用)时，由于没有动态类型检查，因此是不安全的
    //2.用于基本数据类型之间的转换，如把int转换成char, int-->enum, 转换安全需要开发人员保证
    //3.把void指针转成目标类型的指针 (不安全)
    //4.把任何类型的指针转换成void
    //注意：static_cast不能转换掉expression的const, volitate或者_unaligned属性
    
    //dynamic_cast<type_id>(expression)
    //该运算符把expression转换成type_id类型的对象，type_id必须是类的指针，类的引用或者void *,
    //同时如果type_id是指针或者引用则express也必须是相应的类型
    //dynamic_cast主要用于类层次间的上行转化和下行转换，还可以用于类之间的交叉转换
    //在类层次间进行上行转换时，与static_cast效果是一样的，在进行下行转换时，dynamic_cast具有类型检查功能，比static_cast更安全。
    
    //
    //reinpreter_cast<type_id> (expression)
    //说明：type-id必须是一个指针、引用、算术类型、函数指针或者成员指针。
    //它可以把一个指针转换成一个整数，也可以把一个整数转换成一个指针
    //（先把一个指针转换成一个整数，在把该整数转换成原类型的指针，还可以得到原先的指针值）。
    //reinterpret_cast运算符是用来处理无关类型之间的转换；它会产生一个新的值，
    //这个值会有与原始参数（expressoin）有完全相同的比特位。按照reinterpret的字面意思“重新解释”，即对数据的比特位重新解释。
    //
    //从指针类型到一个足够大的整数类型
    //从整数类型或者枚举类型到指针类型
    //从一个指向函数的指针到另一个不同类型的指向函数的指针
    //从一个指向对象的指针到另一个不同类型的指向对象的指针
    //从一个指向类函数成员的指针到另一个指向不同类型的函数成员的指针
    //从一个指向类数据成员的指针到另一个指向不同类型的数据成员的指针
   int a = 49;
   int *pa = &a;
   char *pc = reinterpret_cast<char*>(pa);//int * 到char *,用户自己安全
   cout<<*pc<<endl; //输出字符"1"
    unsigned long b = reinterpret_cast<unsigned long>(pc);//char * 转 unsigned long
   cout<<b<<endl;//输出pc指向地址（即a的地址）对应的整数
   int *pi2 = reinterpret_cast<int *>(b);//unsigned long 转 int*
   cout<<*pi2<<endl; //输出49 
    //const_cast<type_id> (expression)
    //该运算符用来修改类型的const或volatile属性。除了const 或volatile修饰之外， type_id和expression的类型是一样的。
    //常量指针被转化成非常量指针，并且仍然指向原来的对象；常量引用被转换成非常量引用，并且仍然指向原来的对象；常量对象被转换成非常量对象。
}
