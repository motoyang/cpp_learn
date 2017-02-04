//
//  keyword_for.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/4.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <iostream>
#include <vector>

int for_learn() {
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
    
    for (const int& i : v) // access by const reference
        std::cout << i << ' ';
    std::cout << '\n';
    
    for (auto i : v) // access by value, the type of i is int
        std::cout << i << ' ';
    std::cout << '\n';
    
    for (auto&& i : v) // access by reference, the type of i is int&
        std::cout << i << ' ';
    std::cout << '\n';
    
    for (int n : {0, 1, 2, 3, 4, 5}) // the initializer may be a braced-init-list
        std::cout << n << ' ';
    std::cout << '\n';
    
    int a[] = {0, 1, 2, 3, 4, 5};
    for (int n : a) // the initializer may be an array
        std::cout << n << ' ';
    std::cout << '\n';
    
    for (int n : a)
        std::cout << 1 << ' ' << n; // the loop variable need not be used
    std::cout << '\n';
    
    return 0;
}

/*
 Output:
 0 1 2 3 4 5
 0 1 2 3 4 5
 0 1 2 3 4 5
 0 1 2 3 4 5
 0 1 2 3 4 5
 1 1 1 1 1 1
*/
