#include <iostream>
#include <string>
#include <mutex>
#include <exception>
#include <condition_variable>


struct my_exception: public std::exception
{
   std::string s;
   my_exception(std::string st) : s(st) {}
   ~my_exception() throw () {}
   const char* what() const throw() { return s.c_str(); }
};


template<class R>
class future_substate {
    public:
        future_substate(): has_val_bool(false), has_exception_bool(false){}
        void set_val(R value) {
            val = value;
            has_val = true;
        }
        void set_exception(std::string s){
            e = my_exception(s);
            has_exception_bool = true;
        }
        bool has_val() {
            return has_val_bool;
        }
        bool has_exception() {
            return has_exception_bool;
        }
        R get_val() {
            if ((has_exception()) || (!has_val())) {
                throw e;
            }
            return val;
        }
    private:
        mutable std::condition_variable cv;
        mutable std::mutex m;
        R val;
        std::exception e;
        bool has_val_bool;
        bool has_exception_bool;
};


template<class R>
class my_future {
    public:
        my_future() {}
        my_future(std::shared_ptr<future_substate<R>> &s) : state(s) {}
        R get() {
            return state.get_val();
        }
    private:
        std::shared_ptr<future_substate<R>> state;

};


template<class R>
class my_promise {
    public:
        my_promise() : retrieved(false) {}
        my_promise(my_promise && rhs) :
            val(std::move(rhs).val),
            retrieved(std::move(rhs).retrieved) {}

        void set_value(R && r) {
            val = r;
            state->set_val(r);
        }

        R get_value() {
            return val;
        }

        my_future<R> get_future() {
            if (retrieved) {
                throw my_exception("Future Retrieved");
            }
            retrieved = true;
            return my_future<R>(state);
        }

    private:
        R val;
        bool retrieved;
        std::shared_ptr<future_substate<R>> state =
            make_shared<future_substate<R>>(future_substate<R>());
};



int main() {
    return 0;
}
