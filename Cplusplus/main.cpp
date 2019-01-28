#include <iostream>
#include "Constructor.h"

using namespace std;

void constructor_test()
{
    B b;
    C c;
    E e;
    F f;
    F f2 = f;
    cout << "f.a = " << f.a << ", f2.a = " << f2.a << endl; 
}

int main()
{
    //构造函数测试
    constructor_test();


};