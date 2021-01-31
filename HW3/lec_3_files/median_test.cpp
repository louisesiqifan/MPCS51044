#include "median.h"
#include<random>
#include<vector>
#include<algorithm>
#include<iostream>
#include <chrono>
using std::vector;
using std::generate;
using std::uniform_real_distribution;
using std::default_random_engine;
using std::cout;
using std::endl;
using namespace std::chrono;
using namespace mpcs51044;

uniform_real_distribution<> dist(0, 100);
default_random_engine re;

struct Timer {
	// Remove the comment from either of the following two lines
	Timer() : start(system_clock::now()) {}
	time_point<system_clock> start;
	~Timer() {
		cout << duration_cast<milliseconds>(system_clock::now() - start).count() << "ms" << endl;
	}
};

int main()
{
	vector<double> v(10'000'000);
	generate(v.begin(), v.end(), []() { return dist(re); });
	{
		Timer pt;
		cout << "Using sort: " << median_sort(v) << endl;
	}
	{
		Timer pt;
		cout << "Using partial sort: " << median_partial_sort(v) << endl;
	}

	{
		Timer pt;
		cout << "Using nth_element: " << median_nth_element(v) << endl;
	}

	return 0;
}
