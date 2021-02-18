#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
using namespace std;
using namespace fmt;

template <typename T, typename... Args>
class Counter {
    public:
        unsigned int count;
        T (*fcn)(Args...);
        Counter(T (& f)(Args...)) {
            fcn = f;
            count = 0;
        }

        T operator()(Args... args) {
            count ++;
            return fcn(forward<Args>(args)...);
        }
};

int f(double d) {
    return static_cast<int>(2*d);
}
Counter cf(f);

int g(double a, double b){
    return static_cast<int>(a+b);
}
Counter cg(g);


int main() {
    cf(1.3);
    cf(2.4);
    cg(1.5, 2.0);
    cg(3.5, 2.0);
    cout<< format("f was called {} times, g was called {} times.\n", cf.count, cg.count);
}
