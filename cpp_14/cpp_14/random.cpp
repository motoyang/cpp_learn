//
//  random.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/4.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

/*
C++11带来诸多特性,random就是其一.

1. random_device

　　标准库提供了一个非确定性随机数生成设备.在Linux的实现中,是读取/dev/urandom设备;Windows的实现居然是用rand_s,在这里强烈谴责一下.

　　random_device提供()操作符,用来返回一个min()到max()之间的一个数字.如果是Linux(Unix Like或者Unix)下,都可以使用这个来产生高质量的随机数,可以理解为真随机数.
*/

int random_1()
{
    std::random_device rd;
    for(int n=0; n<10; ++n)
        std::cout << rd() << std::endl;
    
    return 0;
}

/*
2. random number engine

　　标准把随机数抽象成随机数引擎和分布两部分.引擎用来产生随机数,分布产生特定分布的随机数(比如平均分布,正太分布等).

　　标准提供三种常用的引擎:linear_congruential_engine,mersenne_twister_engine和subtract_with_carry_engine.第一种是线性同余算法,第二种是梅森旋转算法,第三种带进位的线性同余算法.第一种是最常用的,而且速度也是非常快的; 第二种号称是最好的伪随机数生成器;第三种没用过....

　　随机数引擎接受一个整形参数当作种子,不提供的话,会使用默认值. 推荐使用random_device来产生一个随机数当作种子.(windows下爱咋整咋整,谁叫windows的random_device是调用rand_s)

*/

int random_2()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    for(int n = 0; n < 10; n++)
        std::cout << mt() << std::endl;
    return 0;
}

/*
3. random number distributions

　　标准提供各种各样的分布,不过我们经常用的比较少,比如平均分布,正太分布...使用也很简单

*/

//平均分布
int random_3()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 60);
    for(int n=0; n<10; ++n)
        std::cout << dis(gen) << ' ';
    std::cout << '\n';
    
    return 0;
}

//正太分布
int random_4()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d(0, 3);
    
    std::map<int, int> hist;
    for(int n=0; n<100000; ++n) {
        ++hist[std::round(d(gen))];
    }
    for(auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
        << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    }
    
    return 0;
}

int random_learn()
{
    std::cout << "1 --------" << std::endl;
    random_1();

    std::cout << "2 --------" << std::endl;
    random_2();

    std::cout << "3 --------" << std::endl;
    random_3();

    std::cout << "4 --------" << std::endl;
    random_4();

    return 0;
}
