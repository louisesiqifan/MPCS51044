#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

int main () {
    vector<double> v = {1.1, 1.2, 1.3, 1.4};
    vector<double> w;

    cout << "Original Vector: ";
    for (auto i:v) {
        cout << i << " ";
    }
    cout << "\n";

    transform(v.begin(), v.end(), back_inserter(w), [](const auto n) { return n*n;});

    cout << "New Vector: ";
    for (auto i:w) {
        cout << i << " ";
    }
    cout << "\n";

    cout << "Distance to origin by accumulate and sqrt: ";
    double d = sqrt(accumulate(w.begin(), w.end(), 0.0));
    cout << d << "\n";

    return 0;
}