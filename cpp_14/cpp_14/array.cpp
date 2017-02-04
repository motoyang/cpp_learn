//
//  array.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/4.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

int array_learn()
{
    // construction uses aggregate initialization
    std::array<int, 3> a1{ {1, 2, 3} }; // double-braces required in C++11 (not in C++14)
    std::array<int, 5> a11{11, 22, 33, 44, 55};
    std::for_each(std::rbegin(a11), std::rend(a11), [](auto&& i)->void {
        ++i;
        std::cout << i << ' ';
    });
    std::cout << std::endl;
    
    std::array<int, 3> a2 = {1, 2, 3};  // never required after =
    std::array<std::string, 2> a3 = { std::string("a"), "b" };
    
    // container operations are supported
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(),
                      std::ostream_iterator<int>(std::cout, " "));
    
    std::cout << '\n';
    
    // ranged for loop is supported
    for(const auto& s: a3)
        std::cout << s << ' ';
    std::cout << std::endl;
    
    return 0;
}

/*
Output:
3 2 1
a b
*/
