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
#include <vector>
using namespace std;

class Base{
public:
    Base(){
        cout << this << " Base Constructor" << endl;
    }
    Base(const std::string& name){
        _name = name;
        cout << this << " Base Constructor " << name << endl;
    }
    virtual ~Base(){
        cout << this << " Base Deconstructor" << endl;
    }
    virtual void print(){
        std::cout << "Base print " << _name << std::endl;
    }
private:
    std::string _name;
};

class Derived : public Base{
public:
    Derived(){};
    Derived(const std::string& name, const std::string&sub_name) : 
            Base(name),_sub_name(sub_name) {}
    virtual ~Derived(){}
    void print(){
        std::cout << "Derived print:" << _sub_name << std::endl;
    }
private:
    std::string _sub_name;
};

unique_ptr<Base> test(){
    unique_ptr<Base> xx(new Base("Base"));
    cout << "unique_ptr<Base> test()" << xx.get() << endl;
    return xx;
}

Base* test1(){
    Base *base = new Base("new base");
    cout << "base=" << base << endl;
    return base;
}
char* test2(){
    char xx[] = "xyz";
    cout << "test2:&xx:" << &xx << endl;
    cout << "xx:" << xx << endl;
    return xx;
}


using BaseUniPtr = unique_ptr<Base>;
using BaseSharePtr = shared_ptr<Base>;
typedef std::pair<int, BaseSharePtr> DataPair;
void set_unique_ptr_test(BaseUniPtr base){
    cout << "set_unique_ptr_test base:" << base.get() << endl;
}

void set_share_ptr_test(BaseSharePtr base){
    cout << "set_share_ptr_test base:" << base.get() << endl;
    cout << "base:" << base.use_count() << endl;
}

int main()
{
    #if 0
    shared_ptr<double> pd;
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
    unique_ptr<Base> xx(new Base("parent"));
    unique_ptr<Derived> xx2(new Derived("parent", "son"));
    xx->print();
    xx2->print();
    cout << "xx: " << xx.get() << endl;
    cout << "xx2: " << xx2.get() << endl;
    //std::move后xx为空
    set_unique_ptr_test(std::move(xx));
    cout << "xx:" << xx.get() << endl;
    //xx2 = move(xx); not allowed 
    
    std::cout << "xx2 move to xx" << endl;
    //xx2 move给xx后xx2为空
    xx = move(xx2);
    cout << "xx:" << xx.get() << endl;
    cout << "xx2:" << xx2.get() << endl;

    std::cout << "************" << std::endl;
    std::cout << "xx move to xx3" << endl;
    unique_ptr<Base> xx3 = move(xx);
    cout << "xx:" << xx.get() << endl;
    cout << "xx3" << xx3.get() << endl;
    //xx3 reset后xx3析构，xx3=0
    xx3.reset();
    cout << "xx3 reset:" << xx3.get() << endl;

    std::cout << "************" << std::endl;
    xx3.reset(new Base("test_x3"));
    unique_ptr<Base> xx4(new Base("test_x4"));
    cout << "xx3:" << xx3.get() << endl;
    cout << "xx4:" << xx4.get() << endl;
    cout << "xx3 swap xx4" << endl;
    //互换了指针
    xx3.swap(xx4);
    cout << "xx3:" << xx3.get() << endl;
    cout << "xx4:" << xx4.get() << endl;
    cout << "xx3 = std::move(xx4)" << endl;
    //赋值时会析构xx3,xx4的指针给xx3 xx4为空
    xx3 = std::move(xx4);
    cout << "xx3:" << xx3.get() << endl;
    cout << "xx4:" << xx4.get() << endl;
    
    
    std::cout << "************" << std::endl;
    std::cout << "************" << std::endl;

    unique_ptr<Base> xx5 = test();
    cout << "unique_ptr<Base>xx5:" << xx5.get() << endl;
    Base* xx6 = test1();
    cout << "xx6:" << xx6 << endl;

    char *xx7 = test2();
    cout << "test2 &xx7:" << &xx7 << endl;
    //cout << "xx7:" << xx7 << endl;

    //shared_ptr 引用计数方式管理内存的智能指针，每次赋值的时候引用计数会+1, 对象reset引用计数会-1
    //引用计数为0的时候，delete掉指针对象并调用析构函数
    cout << "*************" << endl;
    cout << "shared_ptr" << endl;
    shared_ptr<Base>yy(new Base("b"));
    cout << "yy.use_count:" << yy.use_count() << endl;
    std::cout << yy.get()  << endl;
    set_share_ptr_test(yy);
    cout << "yy2=yy" << endl; 
    shared_ptr<Base> yy2 = yy;
    cout << "yy=" << yy.get() << endl;
    cout << "yy2=" << yy2.get() << endl;
    cout << "yy_use_count:" << yy.use_count() << endl; 
    cout << "yy2_use_count:" << yy2.use_count() << endl;

    //reset后yy2的引用计数变0
    yy2.reset();
    cout << "yy2 reset" << endl;
    cout << "yy_use_count:" << yy.use_count() << endl; 
    cout << "yy2_use_count:" << yy2.use_count() << endl;
    cout << "yy=" << yy.get() << endl;
    cout << "yy2=" << yy2.get() << endl;
    cout << "yy reset" << endl;
    yy.reset();
    cout << "yy_use_count:" << yy.use_count() << endl; 
    cout << "yy2_use_count:" << yy2.use_count() << endl;
    cout << "yy=" << yy.get() << endl;
    cout << "yy2=" << yy2.get() << endl;
#endif

    std::vector<Base>t1_vec;
    std::vector<BaseSharePtr>t2_vec;
    DataPair *data= new DataPair[5];
    data[0].first = 0;
    data[0].second.reset(new Base("test1"));
    t1_vec.emplace_back(*(data[0].second));
    //引用计数增加
    t2_vec.emplace_back(data[0].second);
    cout << "data[0].second:" << data[0].second.get() << " count:" << data[0].second.use_count() << endl;
    data[0].second.reset(new Base("test2"));
    cout << "data[0].second:" << data[0].second.get() << " count:" << data[0].second.use_count() << endl;
    //BaseSharePtr test2(new Base("test2"));
    //赋值时原来的指向的对象被析构
    //data[0].second = test2;
    //cout << "test2:" << test2.get() << " count:" << test2.use_count() << endl;
    cout << "data[0].second:" << data[0].second.get() << " count:" << data[0].second.use_count() << endl;


    cout << "t2_vec[0]:" << t2_vec[0] << endl;
    //vector clear或者程序退出的时候会析构t2_vec[0]
    //t2_vec.clear();
    //data[0].second.reset();
}
