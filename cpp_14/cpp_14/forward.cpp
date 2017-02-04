//
//  forward.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/4.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <iostream>
#include <memory>
#include <utility>
#include <array>

struct A {
    A(int&& n) { std::cout << "rvalue overload, n=" << n << "\n"; }
    A(int& n)  { std::cout << "lvalue overload, n=" << n << "\n"; }
};

class B {
public:
    template<class T1, class T2, class T3>
    B(T1&& t1, T2&& t2, T3&& t3) :
    a1_{std::forward<T1>(t1)},
    a2_{std::forward<T2>(t2)},
    a3_{std::forward<T3>(t3)}
    {
    }
    
private:
    A a1_, a2_, a3_;
};
/*
template<class T, class U>
std::unique_ptr<T> make_unique1(U&& u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)));
}

template<class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}
*/

int forward_learn()
{
    std::cout << "A\n";
    auto p1 = std::make_unique<A>(2); // rvalue
    int i = 1;
    auto p2 = std::make_unique<A>(i); // lvalue
    auto p3 = std::make_unique<A>(std::move(i));    // rvalue
    
    std::cout << "B\n";
    auto t = std::make_unique<B>(2, i, 3);
    auto t2 = std::make_unique<B>(22, std::move(i), 33);
    
    return 0;
}

/*
 A
 rvalue overload, n=2
 lvalue overload, n=1
 rvalue overload, n=1
 B
 rvalue overload, n=2
 lvalue overload, n=1
 rvalue overload, n=3
 rvalue overload, n=22
 rvalue overload, n=1
 rvalue overload, n=33
*/
