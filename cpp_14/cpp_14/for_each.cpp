//
//  for_each.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/4.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <vector>
#include <algorithm>
#include <iostream>

/*
 std::for_each
 C++  Algorithm library
 Defined in header <algorithm>
 
 template< class InputIt, class UnaryFunction >
 UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );                    (1)
 template< class ExecutionPolicy, class InputIt, class UnaryFunction2 >
 void for_each( ExecutionPolicy&& policy, InputIt first, InputIt last, UnaryFunction2 f );  (2)	(since C++17)

 1) Applies the given function object f to the result of dereferencing every iterator in the range [first, last), in order.
 2) Applies the given function object f to the result of dereferencing every iterator in the range [first, last) (not necessarily in order). The algorithm is executed according to policy. This overload does not participate in overload resolution unless std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> is true.
 For both overloads, if InputIt is a mutable iterator, f may modify the elements of the range through the dereferenced iterator. If f returns a result, the result is ignored.
 
 Parameters
 first, last	-	the range to apply the function to
 policy	-	the execution policy to use. See execution policy for details.
 f	-	function object, to be applied to the result of dereferencing every iterator in the range [first, last)
 The signature of the function should be equivalent to the following:
 void fun(const Type &a);
 The signature does not need to have const &.
 The type Type must be such that an object of type InputIt can be dereferenced and then implicitly converted to Type.
 ​
 Type requirements
 -InputIt must meet the requirements of InputIterator.
 -UnaryFunction must meet the requirements of MoveConstructible. Does not have to be CopyConstructible
 -UnaryFunction2 must meet the requirements of CopyConstructible.
 Return value
 1) f (until C++11) std::move(f) (since C++11)
 2) (nothing)
*/
 
struct Sum
{
    Sum(): sum{0} { }
    Sum(const Sum& s): sum(s.sum) { std::cout << "Sum::Sum(const Sum& s) called." << std::endl; }
    Sum(Sum& s): sum(s.sum) { std::cout << "Sum::Sum(Sum& s) called." << std::endl; }
    Sum(Sum&& s): sum(s.sum) { std::cout << " Sum::Sum(Sum&& s) called." << std::endl; }
    
    void operator()(int n) { sum += n; }
    int sum;
};

int for_each_learn()
{
    std::vector<int> nums{3, 4, 2, 8, 15, 267};
    
    std::cout << "before:\n";
    for (auto const &n : nums)
    {
        std::cout << ' ' << n;
    }
    std::cout << '\n';
    // calls Sum::operator() for each number
    Sum s = std::for_each(nums.begin(), nums.end(), Sum());
    std::cout << "sum: " << s.sum << '\n';
    
    std::for_each(nums.rbegin(), nums.rend(), [](int &n){ n++; });
    std::for_each(nums.begin(), nums.end(), [](auto&& n){ n++; });
    
    // calls Sum::operator() for each number
    auto&& s2 = std::for_each(nums.begin(), nums.end(), Sum());
    
    std::cout << "after:\n";
    for (auto const &n : nums)
    {
        std::cout << ' ' << n;
    }
    std::cout << '\n';
    std::cout << "sum: " << s2.sum << '\n';
    
    return 0;
}

/*
 Output:
 before:
 3 4 2 8 15 267
 Sum::Sum(Sum&& s) called.
 sum: 299
 Sum::Sum(Sum&& s) called.
 after:
 5 6 4 10 17 269
 sum: 311
*/
