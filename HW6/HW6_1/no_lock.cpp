#include <iostream>
#include <thread>
#include <fstream>
using namespace std;


void thread_f() {
    for (int i = 0; i < 100; i++) {
        unique_lock guard(m);
        osyncstream(cout) << "Thread " << this_thread::get_id()
                          << " has been called " << i+1 << " time(s).\n";
    }
}

int main() {
    thread th1(thread_f);
    thread th2(thread_f);
    thread th3(thread_f);
    th1.join();
    th2.join();
    th3.join();
    return 0;
}
