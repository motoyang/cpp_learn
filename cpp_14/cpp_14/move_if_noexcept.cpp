//
//  move_if_noexcept.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/4.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <iostream>
#include <utility>

struct Bad
{
    Bad() {}
    Bad(Bad&&)  // may throw
    {
        std::cout << "Bad. Throwing move constructor called\n";
    }
    Bad(const Bad&) // may throw as well
    {
        std::cout << "Bad. Throwing copy constructor called\n";
    }
};

struct Good
{
    Good() {}
    Good(Good&&) noexcept // will NOT throw
    {
        std::cout << "Good. Non-throwing move constructor called\n";
    }
    Good(const Good&) noexcept // will NOT throw
    {
        std::cout << "Good. Non-throwing copy constructor called\n";
    }
};

int move_if_noexcept_learn()
{
    Good g;
    Bad b;
    Good g2 = std::move_if_noexcept(g);
    Bad b2 = std::move_if_noexcept(b);
    
    return 0;
}

/*
Output:
Good. Non-throwing move constructor called
Bad. Throwing copy constructor called
*/
