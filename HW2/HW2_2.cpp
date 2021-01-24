#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


double median_from_sort (vector<double> v) {
    int n = v.size();
    sort(v.begin(), v.end());
    if (n % 2 == 0) {
        return (v[n/2-1] + v[n/2])/2;
    }
    return v[n/2];
}

double median_from_partial_sort (vector<double> v) {
    int n = v.size();
    partial_sort(v.begin(), v.end(), v.end());
    if (n%2 == 0) {
        return (v[n/2-1] + v[n/2])/2;
    }
    return v[n/2];
}

double median_from_nth_element(vector<double> v) {
    int n = v.size();
    if (n%2 == 0) {
        nth_element(v.begin(), v.begin() + n/2 - 1, v.end());
        nth_element(v.begin(), v.begin() + n/2, v.end());
        return (v[n/2-1] + v[n/2])/2;
    }
    nth_element(v.begin(), v.begin() + n/2, v.end());
    return v[n/2];
}

auto median_of_any_type(vector<auto> v) {
    int n = v.size();
    if (n%2 == 0) {
        nth_element(v.begin(), v.begin() + n/2 - 1, v.end());
        nth_element(v.begin(), v.begin() + n/2, v.end());
        return (double)(v[n/2-1] + v[n/2])/2;
    }
    nth_element(v.begin(), v.begin() + n/2, v.end());
    return (double)v[n/2];
}

int main () {
    vector<double> v = {1.4, 1.2, 1.3, 1.1};
    vector<int> w = {1, 2, 3, 4};

    cout << "Median From Sort: " << median_from_sort(v) << '\n';
    cout << "Median From Partial Sort: " << median_from_partial_sort(v) << '\n';
    cout << "Median From nth Element: " << median_from_nth_element(v) << '\n';

    cout << "Median of any kind: \n";
    cout << "    double: " << median_of_any_type(v) << '\n';
    cout << "    int:    " << median_of_any_type(w) << "\n";

    return 0;
}
