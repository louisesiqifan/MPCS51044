#include <iostream>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;

struct Nth_Power {
    int p;

    int operator()(int q) const {
        return pow(q, p);
    }
};


int main() {
    vector<int> v = { 1, 2, 3, 4, 5 };
    Nth_Power cube{3};
    cout<< cube(7) << endl; // prints 343
    // print first five cubes
    transform(v.begin(), v.end(), ostream_iterator<int>(cout, ", "), cube);
    cout << '\n';
    return 0;
}
