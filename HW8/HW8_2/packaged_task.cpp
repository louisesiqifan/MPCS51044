#include <iostream>
#include <future>
#include <thread>
#include <functional>

// Declaration
template<class>
class my_packaged_task;

// Definition
template<class C, class ...Args>
class my_packaged_task<C(Args...)> {
    public:
        template<class Fnc>
        my_packaged_task(Fnc&& f): fnc(f){}

        my_packaged_task(my_packaged_task&& o):
            p(std::move(o).p), fnc(std::move(o).fnc) {}

        void operator()(Args&&... args) {
            p.set_value(fnc(std::forward<Args>(args)...));
        }

        std::future<C> get_future(){
            return p.get_future();
        }

    private:
        std::function<C(Args...)> fnc;
        std::promise<C> p;

};


int test_fcn(int x, int y) {
    std::cout << "Here" << std::endl;
    return x+y;
}


int main() {
    my_packaged_task<int(int, int)> t(test_fcn);
    std::future<int> res = t.get_future();

    std::thread th(std::move(t), 4, 5);

    th.join();

    std::cout << res.get() << std::endl;
    return 0;
}
