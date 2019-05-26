#ifndef STRING_H_
#define STRING_H_
#include <iostream>
using std::ostream;
using std::istream;
class StringBad
{
    private:
        char *str;
        int len;
        static int num_strings;
        static const int CINLIM=80;
        int test_array[12] = {1};
    public:
        void *test;
        StringBad(const char *s);
        StringBad();
        StringBad(const StringBad &st);
        StringBad & operator=(const StringBad &);
        ~StringBad();
        void *alloc_test();
        void * get_test(){
            return test;
        }
        friend bool operator<(const StringBad &st1, const StringBad &st2);
        friend bool operator>(const StringBad &st1, const StringBad &st2);
        friend bool operator==(const StringBad &st1, const StringBad &st2);
        friend std::ostream & operator<<(std::ostream &os, const StringBad &st);
        friend istream & operator>>(istream &is, StringBad &st);
};
#endif
