#include <vector>
#include <string>
#include <iostream>

#include <iostream>

class TestVector{
    public:
        int i;
        std::vector<int> test_vector;
    private:
        int j;
};

struct C {
    C(int j) { i = j; }
    C(const C& test) { 
        printf("copy constructor:this:%p C:%p\n", this, test );
        std::cout << "A copy was made.\n"<<std::endl;
    }
    int i;
};

C  f(bool cond = false) {
    C first(101);
    C second(102);
    printf("first:%p\n", first);
    // the function may return one of two named objects
    //depending on its argument. RVO might not be applied
    return cond ? first : second;
}
 
struct President
{
    std::string name;
    std::string country;
    int year;
    
    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }
    
    President(President&& other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being moved.\n";
    }
    President& operator=(const President& other) = default;
};
 
int main()
{
        std::vector<President> elections;
        std::cout << "emplace_back:\n";
        elections.emplace_back("Nelson Mandela", "South Africa", 1994);
        
        std::vector<President> reElections;
        std::cout << "\npush_back:\n";
        reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));
        
        std::cout << "\nContents:\n";
        for (President const& president: elections) {
            std::cout << president.name << " was elected president of "
                << president.country << " in " << president.year << ".\n";
        }
        
        for (President const& president: reElections) {
            std::cout << president.name << " was re-elected president of "
                << president.country << " in " << president.year << ".\n";
        }
        
        std::cout << "Hello World!\n";
        C obj = f(true);
        printf("obj:%p\n", obj);

        TestVector test_node;
        test_node.i=100;
        //test_node.test_vector.resize(3);
        test_node.test_vector.push_back(10);
        test_node.test_vector.push_back(20);
        test_node.test_vector.push_back(30);

        std::vector<int> vector1;
        vector1.reserve(4);
        vector1.push_back(10);
        vector1.push_back(20);
        vector1.push_back(30);
        printf("vector1:%p %d %d %d\n", vector1, vector1[0], vector1[1], vector1[2]);
        
        printf("test_node:%p i:%d %p:test_vector[0]:%d test_vector[1]:%d test_vector[2]:%d\n",\
               test_node,  test_node.i, &test_node.test_vector[0], test_node.test_vector[0], test_node.test_vector[1], test_node.test_vector[2]);

        TestVector test1_node = test_node;
        printf("test1_node:%p i:%d %p:test_vector[0]:%d test_vector[1]:%d\n", test1_node, \
                test1_node.i, &test1_node.test_vector[0],test1_node.test_vector[0], test1_node.test_vector[1]);
}
