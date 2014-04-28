#include "F.h"

/*
Consider the following functions:
    fun(a,b,c,d) = c if a>b, d otherwise;
    inc(a) = a+1

Your challenge is to derive the basic mathematical (+, -, *, /, %) and logic
(&, |, ~) operations using only these 2 functions, recursion and the number 0,

F.h provides a simple wrapper for you to test your answer. You must always
work with F objects to represent a number, using:

    F F::fun(const F& a, const F& b, const F& c, const F& d)
        (returns the equivalent to a > b ? c : d )
    F F::inc(const F& a)
        (returns the equivalent to a++)
    F F::zero
        (returns the equivalent to 0)

You will probably need recursion when designing your solution. For instance,
consider this dummy function:

F my_function(const F& arg1, const F& arg2){
    return F::fun(
        arg1,
        arg2,
        my_function(arg1, F::zero),
        F::zero
    );
}

C++ will try to evaluate my_function(arg1, F::zero) before it completes the call
to F::fun, thus causing a stack overflow. You need a binding mechanism as a lazy
evaluation wrapper to solve this:

F my_function(const F& arg1, const F& arg2){
    return F::fun(
        arg1,
        arg2,
        F::bind(&my_function, arg1, F::zero),
        F::zero
    );
}

Then it should work as expected.

You can also stream your result to std::cout, as in:

std::cout << my_function(arg1, arg2) << std::endl;

*/

F zero(F::zero);
F one(F::inc(zero));
F two(F::inc(one));
F three(F::inc(two));

//simple usage of function F::fun
F dummy0(const F& x, const F& y) { return F::fun(x, y, one, zero); }

//making compound statements with F::fun
F dummy1(const F& x, const F& y) { return F::fun(x, y, zero, F::fun(y, x, zero, one)); }

//implementing a recursive function with lazy evaluation of itself
F dummy2(const F& x, const F& y) { return F::fun(x, y, F::bind(&dummy2, x, F::inc(y)), x); }

int main(){

    std::cout << dummy0(three, two) << std::endl;
    std::cout << dummy1(zero, one) << std::endl;
    std::cout << dummy2(three, one) << std::endl;

    return 0;
}
