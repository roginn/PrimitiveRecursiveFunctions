#include <iostream>
#include <functional>

class F {
public:
    typedef std::function<unsigned int (void)> Func;
    typedef std::function<F (void)> CompFunc;

    F(const Func& f) : f_(f), comp(false) {}
    F(const CompFunc& g) : g_(g), comp(true) {}

    static F bind(unsigned int (*to_bind)(unsigned int), unsigned int a)
    { return F((Func) std::bind(to_bind, a)); }

    static F bind(F (*to_bind)(const F&), const F& a)
    { return F((CompFunc) std::bind(to_bind, a)); }

    static F bind(F (*to_bind)(const F&, const F&), const F& a, const F& b)
    { return F((CompFunc) std::bind(to_bind, a, b)); }

    static F bind(F (*to_bind)(const F&, const F&, const F&),
        const F& a, const F& b, const F& c)
    { return F((CompFunc) std::bind(to_bind, a, b, c)); }

    static F bind(F (*to_bind)(const F&, const F&, const F&, const F&),
        const F& a, const F& b, const F& c, const F& d)
    { return F((CompFunc) std::bind(to_bind, a, b, c, d)); }

    static F fun(const F& a, const F& b, const F& c, const F& d)
    { return a > b ? c : d; }

    static F inc(const F& a) { return F::bind(&F::inc_, a()); }
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
