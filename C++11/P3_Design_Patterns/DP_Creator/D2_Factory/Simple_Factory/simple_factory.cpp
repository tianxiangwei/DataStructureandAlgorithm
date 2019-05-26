//创建型模式：简单工厂

#include <stdio.h>

//运算类(其它的加减乘法类从这里继承)
class COperator
{
protected:
    double mFirst;
    double mSecond;
public:
    void setFirst(double value){mFirst = value;}
    double getFirst(){return mFirst;}
    
    void setSecond(double value){mSecond = value;}
    double getSecond(){return mSecond;}
    
    virtual double getResult(){return 0;} 
};

//加法类
class CAdd : public COperator
{
public:
    double getResult()
    {
        return mFirst + mSecond;
    }    
};

//减法类
class CSub : public COperator
{
public: 
    double getResult()
    {
        return mFirst - mSecond;
    }    
};

//乘法类
class CMul : public COperator
{
public:
    double getResult()
    {
        return mFirst * mSecond;
    }    
};

//除法类
class CDiv : public COperator
{
public: 
    double getResult()
    {
         const double P = 0.000000000000001;
         if((-P < mSecond) && (mSecond< P)) //除数不能为0
         {
            return 0;
         }
            
        return mFirst / mSecond;
    }    
};

//简单工厂类
class CSimpleFactory
{
public:
    /**
      *创建具体运算实现类对象的方法
      *@参数：从外部传入的选择条件（+、-、*、/）
      *@返回值：创建好的运算实现类对象
    */
    //将创建函数定义为静态成员函数，可以让客户端省去创建工厂类对象
    static COperator* createOperator(char cOperator)
    {
        COperator* oper = NULL;
        
        switch(cOperator)  //根据客户端传入的参数，选择创建具体的类
        {
        case '+':
            oper = new CAdd();
            break;
        case '-':
            oper = new CSub();
            break;
        case '*':
            oper = new CMul();
            break;
        case '/':
            oper = new CDiv();
            break;            
        }
        
        return oper;
    }
};

int main()
{
    //客户端调用例子
    
    //客户端只需依赖COperator的接口类和工厂类，而无法知道具体的实现类
    //实现了客户端和具体实现类之间的解耦
    COperator* oper =  CSimpleFactory::createOperator('/');
    oper->setFirst(1);
    oper->setSecond(2);
    
    printf("%f + %f = %f\n", oper->getFirst(),oper->getSecond(),oper->getResult());
    
    return 0;
}
