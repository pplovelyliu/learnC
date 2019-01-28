#ifndef _constructor_h_
#define _constructor_h_

#include <iostream>
using namespace std;

class A 
{
public:    
    A()
    {
        cout << "A construct" << endl;
    }

    ~A()
    {
        cout << "~A destructed" << endl;
    }
};

//class member 有defaut constructor， 所以编译器会自动给B增加一个inline 的默认构造器
class B
{
    public: 
        int b;
        A a;    
};

//base class 有默认构造函数，则子类没有声明构造函数的话，编译器也会自动生成一个默认构造函数，用来调用base class 的constructor
class C : public A
{
    public:
     ~C()
     {
         cout << "~C destructed" << endl;
     }
};

//class 内部中虚函数，也会构造默认构造函数， 因为编译器需要生成virtual table用来保存virtual function的地址，class 内部需要生成
//对应的vptr来指向vitural table。
class D
{
    public: 
        virtual void test() = 0;

};

//继承virtual class ，编译会生成默认构造器。因为需要生成vbc指针，用于指向虚基类。
class E : public virtual B
{
    public:
};

class F
{
    public:
        F():a(100)
        {
            // c = 100;
        }
        F(const F &f):a(1000)
        {
            cout << "F copy structor" << endl;
        }
        const int a;
        int b;
};

#endif;