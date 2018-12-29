//面向对象设计原则：LoD迪米特法则
//类间解耦

#include <stdio.h>
#include <list>
using namespace std;

//Girl类
class Girl
{
    
};

//体育委员类
class GroupLeader
{
public:
    //清点女生数量 
    void countGirls(list<Girl>& list)
    {
        printf("Numbers of Girls: %d\n", list.size());
    }    
};

//Teacher类
class Teacher
{
public:
    //老师叫体育委员清点一下女生人数
    void command(GroupLeader& groupLeader)
    {
        //方法内的类，与Teacher不是朋友关系，
        //但这样的设计会使Teacher对Girl类产生依赖，违反Lod法则
        list<Girl> listGirls;
        
        //初始化女生
        for(int i = 0; i< 20; i++)
        {
            Girl g;
            listGirls.push_back(g);//会复制一份过去
        }
        
        groupLeader.countGirls(listGirls);
    }
};

int main()
{
    Teacher teacher;
    GroupLeader groupLeader;
    
    //老师发布命令
    teacher.command(groupLeader);
    
    return 0;
}


//面向对象设计原则：LoD迪米特法则
//类间解耦

#include <stdio.h>
#include <list>
using namespace std;

//Girl类
class Girl
{

};

//体育委员类
class GroupLeader
{
private:
    list<Girl>& listGirls;
public:
    //从构造器传入全班女生
    GroupLeader(list<Girl>& _list):listGirls(_list)
    {

    }

    //清点女生数量
    void countGirls()
    {
        printf("Numbers of Girls: %d\n", listGirls.size());
    }
};

//Teacher类：与Girl类解耦
class Teacher
{
public:
    //老师叫体育委员清点一下女生人数
    void command(GroupLeader& groupLeader)
    {
        groupLeader.countGirls();
    }
};

int main()
{
    Teacher teacher;
    list<Girl> listGirls;

    //初始化女生
    for(int i = 0; i< 20; i++)
    {
        Girl g;
        listGirls.push_back(g);//会复制一份过去
    }

    //
    GroupLeader groupLeader(listGirls);

    //老师发布命令
    teacher.command(groupLeader);

    return 0;
}
