//
//  smart_ptr.cpp
//  cpp_14
//
//  Created by moto2 yang on 2017/2/4.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

struct Foo
{
    Foo()      { std::cout << "Foo::Foo\n";  }
    ~Foo()     { std::cout << "Foo::~Foo\n"; }

    void bar() { std::cout << "Foo::bar\n";  }
};

void f(const Foo &)
{
    std::cout << "f(const Foo&)\n";
}

int unique_ptr_1()
{
//    std::unique_ptr<Foo> p1(new Foo);  // p1 owns Foo
    auto p1 = std::make_unique<Foo>();
    if (p1) p1->bar();
    
    {
        std::unique_ptr<Foo> p2(std::move(p1));  // now p2 owns Foo
        f(*p2);
        
        p1 = std::move(p2);  // ownership returns to p1
        std::cout << "destroying p2...\n";
    }
    
    if (p1) p1->bar();
  
    return 0;
    // Foo instance is destroyed when p1 goes out of scope
}

/*
Output:
Foo::Foo
Foo::bar
f(const Foo&)
destroying p2...
Foo::bar
Foo::~Foo
*/

int unique_learn()
{
    std::cout << "unique_prt_1 ----------------------------" << std::endl;
    unique_ptr_1();
    
    return 0;
}

//--------------------------------------------------

struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // Note: non-virtual destructor is OK here
    ~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // thread-safe, even though the
    // shared use_count is incremented
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
        << "  lp.get() = " << lp.get()
        << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}

int share_ptr_1()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
    
    std::cout << "Created a shared Derived (as a pointer to Base)\n"
    << "  p.get() = " << p.get()
    << ", p.use_count() = " << p.use_count() << '\n';
    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    p.reset(); // release ownership from main
    std::cout << "Shared ownership between 3 threads and released\n"
    << "ownership from main:\n"
    << "  p.get() = " << p.get()
    << ", p.use_count() = " << p.use_count() << '\n';
    t1.join(); t2.join(); t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";
    
    return 0;
}

/*
Possible output:
Base::Base()
Derived::Derived()
Created a shared Derived (as a pointer to Base)
p.get() = 0xc99028, p.use_count() = 1
Shared ownership between 3 threads and released
ownership from main:
p.get() = (nil), p.use_count() = 0
local pointer in a thread:
lp.get() = 0xc99028, lp.use_count() = 3
local pointer in a thread:
lp.get() = 0xc99028, lp.use_count() = 4
local pointer in a thread:
lp.get() = 0xc99028, lp.use_count() = 2
Derived::~Derived()
Base::~Base()
All threads completed, the last one deleted Derived
*/

int share_ptr_learn()
{
    std::cout << "share_ptr_1 ----------------------------" << std::endl;
    share_ptr_1();
    
    return 0;
}
