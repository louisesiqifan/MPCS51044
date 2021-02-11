#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct maxlenftn {
    maxlenftn() { maxlen= 0; }
    void operator()(string s) {
        maxlen = max(maxlen,s.size());
    }
    string::size_type maxlen;
};

int main() {
    /*
    The reason why the original code didn't work is because since c++11,
    for_each() function returns std::move(f), and thus the information
    no longer stores in the original maxf.
    */
    vector<string> names{"Smith", "Jones", "Johnson", "Grant"};
    maxlenftn maxf;
    maxlenftn newf = for_each(names.begin(),names.end(),maxf);
    cout<< newf.maxlen<< endl;
    return 0;
}
