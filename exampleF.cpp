#include "F.h"

/*
F.h provides two functions and one starting value (zero)
for you to work with:

    F::fun(F a, F b, F c, F d) 
        (returns the equivalent to a > b ? c : d )
    F::inc(F a)
        (returns the equivalent to a++)
    F::zero
        (returns the equivalent to 0)

Your challenge is to derive the operations +-*%/ using only these resources.
When writing recursive functions, you will probably need a lazy evaluation
tool. For that, use:
    F my_function(F arg1, F arg2) 
        lazy--> F::bind(&my_function, arg1, arg2)

*/

F zero(F::zero);
F one(F::inc(zero));
F two(F::inc(one));
F three(F::inc(two));

//simple usage of function F::fun
F dummy0(F x, F y) { return F::fun(x, y, one, zero); }

//making compound statements with F::fun
F dummy1(F x, F y) { return F::fun(x, y, zero, F::fun(y, x, zero, one)); }

//implementing a recursive function with lazy evaluation of itself
F dummy2(F x, F y) { return F::fun(x, y, F::bind(&dummy2, x, F::inc(y)), x); }

int main(){

    std::cout << dummy0(three, two) << std::endl;
    std::cout << dummy1(zero, one) << std::endl;
    std::cout << dummy2(three, one) << std::endl;

    return 0;
}
