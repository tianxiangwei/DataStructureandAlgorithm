//创建型模式：抽象工厂模式
//电脑组装
#include <stdio.h>

////////////////////////////////////////////产品（等级）////////////////////////////
//产品等级1：
//1、抽象CPU类
class CPUApi
{
public:
    virtual void calculate() = 0;
};

//1.1 AMD CPU(具体CPU产品类)
class AMDCPU : public CPUApi
{
private:
    int pints;
public:
    AMDCPU(int pints){this->pints = pints;}
    void calculate()
    {
        printf("now in AMD CPU, pints = %d\n",pints);
    }    
};

//1.2 Intel CPU(具体CPU产品类)
class IntelCPU : public CPUApi
{
private:
    int pints;
public:
    IntelCPU(int pints){this->pints = pints;}
    void calculate()
    {
        printf("now in Intel CPU, pints = %d\n",pints);
    }    
};

//产品等级2
//2.抽象主板类
class MainboardApi
{
public:
    virtual void installCPU() = 0;  
};

//2.1 技嘉主板
class GAMainboard : public MainboardApi
{
private:
    int cpuHoles; //CPU插槽的孔数
public:
    GAMainboard(int cpuHoles){this->cpuHoles = cpuHoles;}
    void installCPU()
    {
        printf("now in GAMainboard, cpuHoles = %d\n", cpuHoles);    
    }    
};

//2.2 微星主板
class MSIMainboard : public MainboardApi
{
private:
    int cpuHoles; //CPU插槽的孔数
public:
    MSIMainboard(int cpuHoles){this->cpuHoles = cpuHoles;}
    void installCPU()
    {
        printf("now in MSIMainboard, cpuHoles = %d\n", cpuHoles);    
    }    
};

////////////////////////////////////////////工厂类////////////////////////////
//3.抽象工厂接口，声明创建抽象产品对象的操作
class AbstractFactory
{
public:
    //创建CPU对象
    virtual CPUApi* createCPUApi() = 0;
    
    //创建主板对象
    virtual MainboardApi* createMainboardApi() = 0;    
};

//3.1具体工厂（装机方案1）：Intel的CPU+技嘉主板
//  这里创建的CPU和主板对象是能匹配的，即有约束关系  
class Schema1 : public AbstractFactory
{
public:
    //CPU
    CPUApi* createCPUApi()
    {
        return new IntelCPU(1156);
    }
    
    //主板对象
    MainboardApi* createMainboardApi()
    {
        return new GAMainboard(1156);
    }    
};

//3.2具体工厂（装机方案2）：AMD的CPU+微星主板
//  这里创建的CPU和主板对象是能匹配的，即有约束关系  
class Schema2 : public AbstractFactory
{
public:
    //CPU
    CPUApi* createCPUApi()
    {
        return new AMDCPU(939);
    }
    
    //主板对象
    MainboardApi* createMainboardApi()
    {
        return new MSIMainboard(939);
    }    
};

int main()
{
    //客户端调用例子
    
    //工厂
    AbstractFactory* af = new Schema1(); //可以整体换装机方案
    
    //CPU
    CPUApi* cpu = af->createCPUApi();
    
    //主板
    MainboardApi* mainboard = af->createMainboardApi();
    
    //测试一下配件是否正常
    cpu->calculate();
    mainboard->installCPU();
    
    delete cpu;
    delete mainboard;
    delete af;
    
    return 0;
}
