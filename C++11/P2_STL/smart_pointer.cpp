//智能指针模板 (auto_ptr unique_ptr shared_ptr)
//autoptr C++98提供 C++11已废弃
//智能指针模板都定义了类似指针的对象，可以将new获取(直接或者间接)的地址赋给这种对象
//当智能指针过期时，其析构函数使用delete来释放内存
//要创建智能指针对象，必须包含头文件memory,该文件模板定义，然后使用通常的模板语法来实例化所需类型的指针
/*template<class X> class auto_ptr(){
    public:
        explicit auto_ptr(X *p=0) throw();
};*/

#include <iostream>
#include <string>
#include <memory>
using namespace std;

int main()
{
    std::shared_ptr<double> pd;
    double *p_reg = new double;
    //pd = p_reg; //not allowded (implicit convertion)
    pd = shared_ptr<double>(p_reg); //allowded (explicit convertion)
    //shared_ptr<double> pshared = p_reg; //not allowded (implicit convertion)
    shared_ptr<double> pshared(p_reg); //allowded (explicit convertion)
    
    auto_ptr<string> ps (new string("test"));
    auto_ptr<string> vocation;
    vocation = ps; //对于这种情况如何在赋值后还去使用ps会导致访问野指针的错误,而使用unique_ptr则编译会出错，从而杜绝这种风险。
    //unique_ptr仅当源unique_ptr指针为临时右值时，编译器允许赋值，因此源unique_ptr是临时的，不存在使用其的风险
    
    unique_ptr<string> pu1(new string("test"));
    unique_ptr<string> pu2;
    //pu2 = pu1; //not allowed
    unique_ptr<string> pu3;
    pu3 = unique_ptr<string>(new string("test")); //allowed
    pu3 = std::move(pu1); //allowded  移动构造函数和右值引用

    //两个只能指针指向同一个string对象，会导致程序删除同一个对象两次，一次是ps过期，再一次是vocation过期
    //为解决这个问题，有以下方法：
    //1. 定义赋值运算法，使之进行深赋值，这样两个指针指向了两个不同的对象
    //2. 建立所有权概念 对于特定的对象，只能有一个智能指针可拥有它，这样只有拥有对象的智能指针过期时才会
    //删除对象，这种让赋值操作转让所有权的方法，是auto_ptr和unique_ptr的策略，但是unique_ptr更严格
    //3. 创建带引用计数的智能指针(reference counting),仅当引起计数为0时才delete对象  shared_ptr采用此策略

}
