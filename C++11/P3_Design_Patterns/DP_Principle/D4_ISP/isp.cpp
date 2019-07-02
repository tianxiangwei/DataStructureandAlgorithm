/*
 * ①Manager类代表管理工人的管理者。
 * ②有两类工人，普通和高效的，他们都需要吃饭和工作
 * ③如果这里来了一个机器人（Robot），如果保持现有设计，让Robot去实现IWork接口，就会被迫去实现吃饭的功能，这种情况下IWorker被认为是一个被污染了的接口。需重构，细化出3个接口，一个IWorkable（工作）、IFeedable（吃饭）和IRechargeable（充电）。
 * ④工人类去实现IWorkable和IFeedable接口。Robot只实现IWorkable接口和 IRechargeable接口。*/

//面向对象设计原则：ISP接口隔离原则
//细化接口

#include <stdio.h>

//IWorkable接口：工作
class IWorkable
{
public:
    virtual void work() = 0;
};

//IFeedable接口：吃饭
class IFeedable
{
public:
    virtual void eat() = 0;
};

//IRechargeable接口：充电
class IRechargeable
{
public:
    virtual void recharge() = 0;
};

//CommonWorker类：普通工人
class CommonWorker : public IWorkable, public IFeedable
{
public:
    void eat(){printf("Common Worker eat()...\n");}
    void work(){printf("Common Worker work()...\n");}
};

//EfficentWork类：高效工人
class EfficentWork : public IWorkable, public IFeedable
{
public:
    void eat(){printf("Efficent Worker eat()....\n");}
    void work(){printf("Efficent Worker work()...\n");}
};

//Robot类：机器人
class Robot : public IWorkable, public IRechargeable
{
public:
    void recharge(){printf("Robot recharge()...\n");}
    void work(){printf("Robot work()...\n");}
};

//Manager类：管理者
class Manager
{
private:
    IWorkable* worker;
public:
    void setWorker(IWorkable* w){worker = w;}
    void manage(){worker->work();}
};
int main()
{

    CommonWorker cmw;
    EfficentWork efw;
    Robot rb;

    Manager mn;

    //管理员让普通工人工作
    mn.setWorker(&cmw);
    mn.manage();

    //管理员让高效工人工作
    mn.setWorker(&efw);
    mn.manage();

    //管理员让机器人工作
    mn.setWorker(&rb);
    mn.manage();

    return 0;
}
