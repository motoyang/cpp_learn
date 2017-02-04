//
//  variadic.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/4.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <iostream>
#include <cstdarg>

void simple_printf(const char* fmt...)
{
    va_list args;
    va_start(args, fmt);
    
    while (*fmt != '\0') {
        if (*fmt == 'd') {
            int i = va_arg(args, int);
            std::cout << i << '\n';
        } else if (*fmt == 'c') {
            // note automatic conversion to integral type
            int c = va_arg(args, int);
            std::cout << static_cast<char>(c) << '\n';
        } else if (*fmt == 'f') {
            double d = va_arg(args, double);
            std::cout << d << '\n';
        }
        ++fmt;
    }
    
    va_end(args);
}

int variadic_learn()
{
    simple_printf("dcff", 3, 'a', 1.999, 42.5);
    
    return 0;
}

/*
Output:
3
a
1.999
42.5
*/
