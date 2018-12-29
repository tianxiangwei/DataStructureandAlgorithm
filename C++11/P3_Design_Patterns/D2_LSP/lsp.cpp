#include <stdio.h>

class Shape
{  
};

class Rectangle : public Shape
{
    
};

class Father
{
public:
    virtual void drawShape(Shape s) //
    {
        printf("Father:drawShape(Shape s)\n");
    }
    
    virtual void showShape(Rectangle r) //
    {
        printf("Father:ShowShape(Rectangle r)\n");       
    }
    
    Shape CreateShape()
    {
        Shape s;
        printf("Father: Shape CreateShape()");
        return s;
    }
};

class Son : public Father
{
public:

    //对于C++而言，重载只能发生在同一作用域。显示Son和Father是不同作用域
    //所以，下面发生的是隐藏，而不是重载！因此，当使用子类时，不管下列
    //函数中的形参是否比父类更严格，只要同名，父类virtual一律被隐藏。

    //子类的形参类型比父类更严格
    virtual void drawShape(Rectangle r)  
    {
        printf("Son:drawShape(Rectangle r)\n");        
    } 
    
    virtual void drawShape(Shape s) //
    {
        printf("Son:drawShape(Shape s)\n");
    }
    
    //子类的形参类型比父类严宽松
    virtual void showShape(Shape s)
    {
        printf("Son:showShape(Shape s)\n");        
    }   
    
    virtual void showShape(Rectangle r) //
    {
        printf("Son:ShowShape(Rectangle r)\n");       
    }

    //返回值类型比父类严格
    Rectangle CreateShape()
    {
        Rectangle r;
        printf("Son: Rectangle CreateShape()\n");
        
        return r;
    } 
};

int main()
{
    //当遵循LSP原则时，使用父类地方都可以用子类替换

    //Father* f = new Father(); //该行可用子类替换    
    //Son* f = new Son(); //用子类替换父类出现的地方

    Father* f = new Son();
    Rectangle r;
    
    //子类形参类型更严格时，下一行输出结果会发生变化，不符合LSP原则
    f->drawShape(r); //Father类型的f时，调用父类的drawShape(Shape s)
                     //Son类型的f时，发生隐藏，会匹配子类的drawShape
    
    //子类形参类型更宽松时，对于C++而言，会因发生隐藏而不符合LSP原则。但Java发生重载，会符合LSP
    f->showShape(r); //Father类型的f时，直接匹配父类的showShape(Rectangle r)
                     //Son类型的f时，因发生隐藏，会匹配子类的showShape(Shape s)
                  
    //子类的返回值类型更严格
    Shape s = f->CreateShape(); //替换为子类时，返回值为Rectangle，比Shape类型小，这种赋值是合法的
    
    delete f;
    
    return 0;
}
