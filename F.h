#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>

class F {
public:
    typedef boost::function<unsigned int (void)> Func;
    typedef boost::function<F (void)> CompFunc;
    
    F(const Func& f) : f_(f), comp(false) {}
    F(const CompFunc& g) : g_(g), comp(true) {}

    static F bind(unsigned int (*to_bind)(unsigned int), unsigned int a)
    { return F(Func(boost::bind(to_bind, a))); }
    static F bind(F (*to_bind)(F), const F& a)
    { return F(CompFunc(boost::bind(to_bind, a))); }
    static F bind(F (*to_bind)(F, F), const F& a, const F& b)
    { return F(CompFunc(boost::bind(to_bind, a, b))); }
    static F bind(F (*to_bind)(F, F, F), const F& a, const F& b, const F& c)
    { return F(CompFunc(boost::bind(to_bind, a, b, c))); }
    static F bind(F (*to_bind)(F, F, F, F), const F& a, const F& b, const F& c, const F& d)
    { return F(CompFunc(boost::bind(to_bind, a, b, c, d))); }

    static F fun(F a, F b, F c, F d) { return a > b ? c : d; }
    static F inc(F a) { return F::bind(&F::inc_, a()); }
    const static F zero;

private:
    unsigned int operator()() const { return comp ? g_()() : f_(); }
    bool operator>(const F& o) const { return operator()() > o(); }
    
    Func f_;
    CompFunc g_;
    bool comp;
    static unsigned int zero_() { return 0; }
    static unsigned int inc_(unsigned int x) { return x+1; }
    friend std::ostream & operator<<(std::ostream&, const F&);    
};

const F F::zero(Func(&F::zero_));
std::ostream & operator<<(std::ostream& os, const F& f) { return os << f(); }
