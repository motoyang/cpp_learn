//
//  function.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/3.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <functional>
#include <iostream>
using namespace std;

std::function<int(int)> Functional;

// 普通函数
int TestFunc(int a)
{
    return a;
}

// Lambda表达式
auto lambda = [](int a)->int{ return a; };

// 仿函数(functor)
class Functor
{
public:
    int operator()(int a)
    {
        return a;
    }
};

// 1.类成员函数
// 2.类静态函数
class TestClass
{
public:
    int ClassMember(int a) { return a; }
    static int StaticMember(int a) { return a; }
};

// 注意其中对类成员函数bind的做法！！！
int function_learn()
{
    // 普通函数
    Functional = TestFunc;
    int result = Functional(10);
    cout << "普通函数："<< result << endl;
    
    // Lambda表达式
    Functional = lambda;
    result = Functional(20);
    cout << "Lambda表达式："<< result << endl;
    
    // 仿函数
    Functor testFunctor;
    Functional = testFunctor;
    result = Functional(30);
    cout << "仿函数："<< result << endl;
    
    // 类成员函数
    TestClass testObj;
    Functional = std::bind(&TestClass::ClassMember, testObj, std::placeholders::_1);
    result = Functional(40);
    cout << "类成员函数："<< result << endl;
    
    // 类静态函数
    Functional = TestClass::StaticMember;
    result = Functional(50);
    cout << "类静态函数："<< result << endl;
    
    return 0;
}

/*
 总结了简单的用法以后，来看看一些需要注意的事项：
 
 关于可调用实体转换为std::function对象需要遵守以下两条原则：
 转换后的std::function对象的参数能转换为可调用实体的参数；
 可调用实体的返回值能转换为std::function对象的返回值。
 std::function对象最大的用处就是在实现函数回调，使用者需要注意，它不能被用来检查相等或者不相等，但是可以与NULL或者nullptr进行比较。
*/
