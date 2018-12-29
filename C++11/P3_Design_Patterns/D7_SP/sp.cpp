2. 单例模式的实现

（1）懒汉式：

　　①其特点是延迟加载，典型的以“时间换空间”做法。即只会在全局访问方法首次被调用时才被创建。

　　②问题：new出来的实例不能自动释放，可能存在内存泄漏问题。其解决方法有2种。

　　　　A.方法1：在单例类内部定义专有的嵌套类，并在单例类定义一个私有的专门用于释放的静态成员，当程序结束析构全局变量时，会自动调用并释放这个单例。

　　　　B.方法2：在单例类提供一个专门用于释放的静态成员函数，并在需要时手动释放。

　　③在实际项目中，单例一般是个全局变量，它的生命期随软件运行结束而自然终止。也就没有内存泄漏，但是如果单例中用到了一个文件锁、文件句柄或数据库连接，这些并不会随程序的关闭而立即关闭，必须在程序关闭前进行手动释放。

//懒汉式1
//创建型模式：单例模式

#include <stdio.h>

//懒汉式1:缺点，须手工释放
class CSingleton
{
public:
    //提供全局访问的访问点
    static CSingleton* getInstance()
    {
        if(m_pInstance == NULL)
        {
            m_pInstance = new CSingleton();
        }
        
        return m_pInstance;
    }
    
    //清除：须手工调用
    static void clearInstance()
    {
        if(m_pInstance != NULL)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    }
    
private:
    //将构造函数设为私有属性
    CSingleton(){};
    
    //把复制构造函数和=操作符也设为私有,防止被复制
    CSingleton(const CSingleton&){}
    CSingleton& operator=(const CSingleton&){}
    
    static CSingleton* m_pInstance;   
};

CSingleton* CSingleton::m_pInstance = NULL; 

int main()
{
    CSingleton* s1 = CSingleton::getInstance();
    CSingleton* s2 = CSingleton::getInstance();
    
    printf("s1 = %p\n", s1);
    printf("s2 = %p\n", s2);
    
    CSingleton::destroyInstance();
    
    return 0;
}

//创建型模式：单例模式

#include <stdio.h>

//懒汉式2:可自动回收垃圾
class CSingleton
{
public:
    //提供全局访问的访问点
    static CSingleton* getInstance()
    {
        if(m_pInstance == NULL)
        {
            m_pInstance = new CSingleton();
        }

        return m_pInstance;
    }

private:
    //将构造函数设为私有属性
    CSingleton(){};
    static CSingleton* m_pInstance;

    //内部类，用于垃圾回收
    class GC
    {
    public:
        ~GC()
        {
            //在这里销毁资源，比如数据库连接，句柄等。
            if(m_pInstance != NULL)
            {
                delete m_pInstance;
                m_pInstance = NULL;
                printf("test: ~GC\n");
            }
        }
    };

    static GC gc;

};

//静态成员变量的初始化
CSingleton* CSingleton::m_pInstance = NULL;

//全局静态变量，会被自动销毁，从而实现对单例的垃圾回收
CSingleton::GC CSingleton::gc;

int main()
{
    CSingleton* s1 = CSingleton::getInstance();
    CSingleton* s2 = CSingleton::getInstance();

    printf("s1 = %p\n", s1);
    printf("s2 = %p\n", s2);

    return 0;
}


（2）饿汉式：其特点是一开始就加载了，典型的“空间换时间”作法。因为一开始就创建了实例，
所以每次用时直接返回就好了
//创建型模式：单例模式

#include <stdio.h>

//饿汉式:多线程安全
class CSingleton
{
public:
    //提供全局访问的访问点
    static CSingleton* getInstance()
    {
        static CSingleton instance;
        return &instance;
    }

private:
    //将构造函数设为私有属性
    CSingleton(){};
};

int main()
{
    CSingleton* s1 = CSingleton::getInstance();
    CSingleton* s2 = CSingleton::getInstance();

    printf("s1 = %p\n", s1);
    printf("s2 = %p\n", s2);

    return 0;
}

（3）双重检查

//创建型模式：单例模式

#include <stdio.h>
#include <windows.h>

class Lock
{
private:
    HANDLE m_hMutex;
public:
    Lock(){m_hMutex = CreateMutex(NULL, FALSE, NULL);}
    ~Lock(){CloseHandle(m_hMutex);}

    void lock(){WaitForSingleObject(m_hMutex, INFINITE);}
    void unlock(){ReleaseMutex(m_hMutex);}
};

//多线程下的单例模式：处理懒汉式，因为饿汉式是线程安全的
class CSingleton
{
public:
    //提供全局访问的访问点
    static CSingleton* getInstance()
    {
        //双检查
        if(m_pInstance == NULL) //第1次检查
        {
            m_lock.lock();
            if(m_pInstance == NULL) //第2次检查
            {
                m_pInstance = new CSingleton;
            }
           m_lock.unlock();
        }
        return m_pInstance;
    }

private:
    //将构造函数设为私有属性
    CSingleton(){};
    static CSingleton* m_pInstance;
    static Lock m_lock;
};

CSingleton* CSingleton::m_pInstance = NULL;
Lock CSingleton::m_lock;

//线程函数，用来测试的
DWORD WINAPI ThreadProc(PVOID pvParam)
{
    CSingleton* s = CSingleton::getInstance();

    printf("thread:%d, address = %p\n",(int)pvParam, s);

    Sleep(1000);

    return 0;
}

int main()
{
    const int iCount = 64;
    HANDLE hThread[iCount];

    for(int i = 0; i< iCount; i++)
    {
        hThread[i] = CreateThread(NULL,0,ThreadProc,(LPVOID)i,0,NULL);
    }

    //注意：WaitForMultipleObjects最多能等待64个内核对象
    WaitForMultipleObjects(iCount, hThread, TRUE, INFINITE);

    for(int i = 0; i< iCount; i++)
        CloseHandle(hThread[i]);

    return 0;
}
