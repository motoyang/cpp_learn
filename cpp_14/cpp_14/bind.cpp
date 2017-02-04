//
//  bind.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/3.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

static int TestFunc(int a, char c, float f)
{
    cout << a << endl;
    cout << c << endl;
    cout << f << endl;
    
    return a;
}

int bind_1()
{
    auto bindFunc1 = bind(TestFunc, std::placeholders::_1, 'A', 100.1);
    bindFunc1(10);
    bindFunc1(1, 2, 3, 4, 5);
    
    cout << "=================================\n";
    
    auto bindFunc2 = bind(TestFunc, std::placeholders::_2, std::placeholders::_1, 100.1);
    bindFunc2('B', 10);
    bindFunc2(1, 2, 3, 4, 5);
    
    cout << "=================================\n";
    
    auto bindFunc3 = bind(TestFunc, std::placeholders::_2, std::placeholders::_3, std::placeholders::_1);
    bindFunc3(100.1, 30, 'C');
    
    return 0;
}


// bind1st和bind2nd在c++11后可以不再使用
// bind提供了更方便、更宽泛的用途
void bind_2()
{
    vector<int> coll;
    for (int i = 1; i <= 15; ++i)
    {
        coll.push_back(i);
    }
    
    // 查找元素值大于10的元素的个数
    // 也就是使得10 < elem成立的元素个数
    long res = count_if(coll.begin(), coll.end(), bind1st(less<int>(), 10));
    cout << "bind1st(less<int>(), 10) is " << res << endl;
    
    // 查找元素值小于10的元素的个数
    // 也就是使得elem < 10成立的元素个数
    res = count_if(coll.begin(), coll.end(), bind2nd(less<int>(), 10));
    cout << "bind2nd(less<int>(), 10) "<< res << endl;

    res = count_if(begin(coll), end(coll), bind(less<int>(), 10, placeholders::_1));
    cout << "bind(less<int>(), 10, placeholders::_1) is "<< res << endl;

    res = count_if(begin(coll), end(coll), bind(less<int>(), placeholders::_1, 10));
    cout << "bind(less<int>(), placeholders::_1, 10) is "<< res << endl;

    
    auto a = bind(less<int>(), 5, placeholders::_1);
    bool b = a(7);
    cout << "b = " << b << endl;
    res = count_if(begin(coll), end(coll), a);
}

class View
{
public:
    void onClick(int x, int y)
    {
        cout << "X : " << x << ", Y : " << y << endl;
    }
};

// 定义function类型, 三个参数
function<void(View, int, int)> clickCallback;

int bind_3()
{
    View button;
    
    // 指向成员函数
    clickCallback = &View::onClick;
    
    // 进行调用
    clickCallback(button, 10, 123);
    
    
    return 0;
}

int bind_learn()
{
    bind_1();
    bind_2();
    bind_3();
    
    return 0;
}


/*
 以下是使用std::bind的一些需要注意的地方：
 
 bind预先绑定的参数需要传具体的变量或值进去，对于预先绑定的参数，是pass-by-value的；
 对于不事先绑定的参数，需要传std::placeholders进去，从_1开始，依次递增。placeholder是pass-by-reference的；
 bind的返回值是可调用实体，可以直接赋给std::function对象；
 对于绑定的指针、引用类型的参数，使用者需要保证在可调用实体调用之前，这些参数是可用的；
 类的this可以通过对象或者指针来绑定。
*/
