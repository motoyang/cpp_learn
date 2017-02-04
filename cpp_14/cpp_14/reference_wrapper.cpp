//
//  reference_wrapper.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/4.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <numeric>
#include <random>
#include <functional>

int shuffle_learn()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::random_device rd;
    std::mt19937 g(rd());
    
    std::shuffle(v.begin(), v.end(), g);
    
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    return 0;
}

int reference_wrapper_learn()
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);
    
    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());
//    std::vector<int&> v(l.begin(), l.end());      // 编译错误
    
    // can't use shuffle on a list (requires random access), but can use it on a vector
    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});
//    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});       ???
  
    std::cout << "Contents of the list: ";
    for (int n : l) std::cout << n << ' '; std::cout << '\n';
    
    std::cout << "Contents of the list, as seen through a shuffled vector: ";
    for (int i : v) std::cout << i << ' '; std::cout << '\n';
    
    std::cout << "Doubling the values in the initial list...\n";
    for (int& i : l) {
        i *= 2;
    }
    
    std::cout << "Contents of the list, as seen through a shuffled vector: ";
    for (int i : v) std::cout << i << ' '; std::cout << '\n';
    
    return 0;
}

/*
Possible output:
Contents of the list: -4 -3 -2 -1 0 1 2 3 4 5
Contents of the list, as seen through a shuffled vector: -1 2 -2 1 5 0 3 -3 -4 4
Doubling the values in the initial list...
Contents of the list, as seen through a shuffled vector: -2 4 -4 2 10 0 6 -6 -8 8
*/
