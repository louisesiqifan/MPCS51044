#include <iostream>
#include <future>
#include <thread>
#include <functional>


int test_fcn(int x, int y) {
    return x+y;
}


template<typename Func, typename ...Args>
auto my_async(Func f, Args ...args) {
    using T = decltype(f(args...));
    std::packaged_task<T(Args...)> task(f);
    std::future<T> result = task.get_future();

    std::thread th(std::move(task), (args)...);
    th.join();

    return result;
}


int main() {
    auto res = my_async(test_fcn, 1, 2);
    std::cout << res.get() << "\n";
    return 0;
}
