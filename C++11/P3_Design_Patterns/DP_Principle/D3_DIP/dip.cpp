//面向对象设计原则：DIP依赖倒置原则
//司机可开任何汽车——依赖抽象/接口

#include <stdio.h>

//汽车接口
class ICar
{
public:
    virtual void run() = 0;
};

//奔驰车类
class Benz : public ICar
{
public:
    void run(){printf("Benz runing...\n");}
};

//宝马车类
class BWM : public ICar
{
public:
    void run(){printf("BWM runing...\n");}
};

//司机接口
class IDriver
{
public:
    //是司机应该会驾驶汽车
    virtual void drive(ICar& car) = 0; //依赖接口
};

//司机类
class Driver : public IDriver
{
public:
    void drive(ICar& car) //实现接口
    {
        car.run();
    }
};

int main()
{
    Driver zhangSan;
    Benz benz;
    BWM  bwm;
    
    //张三开奔驰车
    zhangSan.drive(benz); 
    
    //张三开宝马
    zhangSan.drive(bwm);
    
    return 0;
}
