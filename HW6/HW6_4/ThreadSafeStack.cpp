#include"ThreadSafeStack.h"
#include<thread>
#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace mpcs51044;
using namespace std;
size_t const reps{100'000};
size_t const threadCount{10};
ThreadSafeStack<int> s;

void pushnpop()
{
  for (size_t i = 0; i < reps; i++)
    s.push(i);
    s.pop();
    if (s.empty()) {
        s.push(2);
    }
    else {
        s.push(3);
    }
}

int main(){
    vector<thread> threads;
    auto start = chrono::high_resolution_clock::now();
    for (size_t k = 0; k < threadCount; k++){
        threads.push_back(thread(pushnpop));
    }
    for (auto &thr : threads){
        thr.join();
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Elapsed time is " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
    return 0;
}
