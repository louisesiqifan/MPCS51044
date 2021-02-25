#ifndef STACK_H
#  define STACK_H

#include<mutex>
#include<shared_mutex>
#include<stack>
#include<numeric>

namespace mpcs51044 {
    template <typename T> class ThreadSafeStack {
        private:
            std::stack<T> stack;
            std::shared_mutex mutable mtx;
        public:
            void push(T item) {
                std::unique_lock lock(mtx);
                stack.push(item);
            }
            void pop() {
                std::unique_lock lock(mtx);
                stack.pop();
            }
            T top() {
                std::shared_lock lock(mtx);
                return stack.top();
            }
            bool empty() {
                std::shared_lock lock(mtx);
                return stack.empty();
            }
            int size() {
                std::shared_lock lock(mtx);
                return stack.size();
            }
    };
}
#endif
