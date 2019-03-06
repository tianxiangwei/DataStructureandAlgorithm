#include <iostream>
#include <functional>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <iterator>

/*成员模板(member template) 既可以在普通类(ordinary class), 也可以在类模板(class template);

在普通类中, 在使用成员函数时, 不用提供模板参数, 函数可以根据使用的参数,

自动推导(deduce)模板实参(template argument)对应模板形参(template parameter);

在类模板中, 成员函数的模板参数(template parameter)可以和类的模板参数不同, 
但在定义(definition)中,必须添加两个模板参数列表(template parameter list), 
第一个为类的, 第二个为成员函数的;
*/

//函数模板默认参数
template <typename T, typename F = std::less<T>>
int compare (const T &v1, const T &v2, F f = F())
{
	if (f(v1, v2)) return -1;
	if (f(v2, v1)) return 1;
	return 0;
}
 
class DebugDelete {
public:
	DebugDelete (std::ostream &s = std::cerr) : os (s) { }
	template <typename T> void operator() (T *p) const {
		os << "deleting unique_ptr" << std::endl; delete p;
	}
private:
	std::ostream &os;
};
 
template <typename T> class Blob {
public:
	template <typename It> Blob (It b, It e);
	/*template <typename It> Blob (It b, It e) {
		std::sort(b, e);
	}*/
};
 
template <typename T>
template <typename It>
Blob<T>::Blob (It b, It e) {
		std::sort(b, e); //容器需要允许被排序
}
 
int main (void) {
 
	std::cout << "compare (0, 42) = " << compare (0, 42) << std::endl;
 
	double* p = new double;
	DebugDelete d;
	d(p); //使用时, 可以自动推倒模板
	int* ip = new int;
	DebugDelete() (ip);
	std::unique_ptr<int, DebugDelete> pi (new int, DebugDelete());
	std::unique_ptr<std::string, DebugDelete> ps (new std::string, DebugDelete());
 
	int ia[] = {9, 8, 7, 6, 5};
	std::vector<long> vi = {5, 4, 3, 2, 1, 0};
	std::deque<std::string> w = {"lady", "girl", "woman", "now"};
 
	Blob<int> a1(std::begin(ia), std::end(ia));
	Blob<int> a2(vi.begin(), vi.end());
	Blob<std::string> a3(w.begin(), w.end());
 
	std::cout << "int ia[] = ";
	for (const auto i : ia) { std::cout << i << " "; }
	std::cout << std::endl;
	std::cout << "std::vector<long> vi = ";
	for (const auto i : vi) { std::cout << i << " "; }
	std::cout << std::endl;
	std::cout << "std::list<const char*> w = ";
	for (const auto i : w) { std::cout << i << " "; }
	std::cout << std::endl;
 
	return 0;
 
}

