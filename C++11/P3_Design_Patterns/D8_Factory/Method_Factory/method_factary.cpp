//创建型模式：工厂方法模式

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

//工厂类（接口）
class CFactory
{
public:
    virtual COperator* createOperator() = 0;//由子类去实现
};

//加法工厂类
class CAddFactory : public CFactory
{
public:
    COperator* createOperator()
    {
        return new CAdd();
    }
};

//减法工厂类
class CSubFactory : public CFactory
{
public:
    COperator* createOperator()
    {
        return new CSub();
    }
};

//乘法工厂类
class CMulFactory : public CFactory
{
public:
    COperator* createOperator()
    {
        return new CMul();
    }
};

//除法工厂类
class CDivFactory : public CFactory
{
public:
    COperator* createOperator()
    {
        return new CDiv();
    }
};

int main()
{
    //客户端调用例子
    
    //客户端只需依赖COperator的接口类和工厂类，而无法知道具体的实现类
    //实现了客户端和具体实现类之间的解耦
    CFactory* ft= new CDivFactory(); //除法工厂
    COperator* oper =  ft->createOperator(); 
    oper->setFirst(1);
    oper->setSecond(2);
    
    printf("%f + %f = %f\n", oper->getFirst(),oper->getSecond(),oper->getResult());
    
    delete oper;
    delete ft;
    
    return 0;
}
