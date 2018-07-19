#include <iostream>
using namespace std;
template <typename T>
class cycleQueue
{
    private:
        unsigned int m_size;
        int m_front;
        int m_rear;
        T *m_data;
    public:
        cycleQueue(unsigned size):m_size(size), m_front(0), m_rear(0)
        {   
            m_data = new T[size];
        }   
        
        ~cycleQueue()
        {   
            delete [] m_data;
        }
        
        bool isEmpty()
        {   
            return m_front == m_rear;
        }   
        
        bool isFull() 
        {   
            return m_front == (m_rear + 1)%m_size;
        }
        
        void push(T ele)throw(bad_exception)
        {
            if(isFull())
            {
                   throw bad_exception();
            } 
            m_data[m_rear] = ele;
            m_rear = (m_rear + 1)%m_size;
            std::cout<<"m_rear:"<<m_rear<<std::endl;
        }

        T pop() throw(bad_exception)
        {
            if(isEmpty())
            {
                std::cout<<"queue is empty"<<" m_front:"<<m_front<<" m_rear:"<<m_rear<<std::endl;
                throw bad_exception();
            }
            T tmp = m_data[m_front];
            m_front = (m_front + 1)%m_size;
            std::cout<<"m_front:"<<m_front<<std::endl;
            return tmp;
        }
};

int main()
{
    cycleQueue<int> q(5);
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    for (int i = 0; i < 4 ; i++)
       cout << q.pop() << endl;
    q.push(5);
    q.push(5);
    q.push(5);
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;

    //queue is empty
    cout << q.pop() << endl;
    return 0;
}
