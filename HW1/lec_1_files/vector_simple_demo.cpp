#include<vector>
#include<iostream>
using namespace std;
int main()
{
  vector<int> v = { 1, 2 }; // Init a vector of ints
  v.push_back(4); // Add an element on to the end
  for (auto i : v) {
    cout << i << ", ";
  } // Prints "1, 2, 4,"

  for (int j = 0; j < v.size(); j++)
    cout << v[j] << ", ";
  return 0;
}
