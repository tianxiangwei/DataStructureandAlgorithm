#include <iostream>
#include <future>
#include <thread>

using namespace std;
class Person
{
public:
    Person(int v) {
        value = v;
        std::cout << "Cons" <<value<< std::endl;
    }
    ~Person() {
        std::cout << "Des" <<value<< std::endl;
    }

    int value;

};

typedef std::shared_ptr<Person> PersonPtr;

void test(PersonPtr obj){
    std::cout << "obj:" << obj.get() << " count:" << obj.use_count() << std::endl; 
    std::cout << "value:" << obj->value << std::endl; 
}

int main()
{
    std::shared_ptr<Person> p1(new Person(1));// Person(1)的引用计数为1
    std::cout << "p1:" << p1.get() << " count:" << p1.use_count() << std::endl;
    test(p1);
    std::shared_ptr<Person> p2 = std::make_shared<Person>(2);
    std::cout << "p1:" << p2.get() << " count:" << p2.use_count() << std::endl;

    p1.reset(new Person(3));// 首先生成新对象，然后引用计数减1，引用计数为0，故析构Person(1)
                            // 最后将新对象的指针交给智能指针
    
    std::cout << "p1:" << p1.get() << " count:" << p1.use_count() << std::endl;
    std::cout << "after p3 =p1" << std::endl;
    std::shared_ptr<Person> p3 = p1;//现在p1和p3同时指向Person(3)，Person(3)的引用计数为2
    std::cout << "p1:" << p1.get() << " count:" << p1.use_count() << std::endl;
    std::cout << "p3:" << p1.get() << " count:" << p3.use_count() << std::endl;

    std::cout << "after p1 reset" << std::endl;
    p1.reset();//Person(3)的引用计数为1
    std::cout << "p1:" << p1.get() << " count:" << p1.use_count() << std::endl;
    std::cout << "p3:" << p3.get() << " count:" << p3.use_count() << std::endl;
    p3.reset();//Person(3)的引用计数为0，析构Person(3)
    std::cout << "after p3 reset" << std::endl;
    std::cout << "p1:" << p1.get() << " count:" << p1.use_count() << std::endl;
    std::cout << "p3:" << p3.get() << " count:" << p3.use_count() << std::endl;
    return 0;
}
