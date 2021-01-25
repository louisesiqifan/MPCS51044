#include <vector>
#include <iostream>
using namespace std;


struct Pascal_Triangle {
    Pascal_Triangle (int k): n{k} {}
    int n;

    vector<vector<int>> construct_pascal_triangle () {
        //Construct the first n rows of the Pascal Triangle.
        vector<vector<int>> triangle = { {1} };
        int row_num = 1;
        while (row_num < n) {
            int col_num = 1;
            vector<int> row = {1};
            while (col_num < row_num) {
                row.push_back(triangle[row_num-1][col_num-1] + triangle[row_num-1][col_num]);
                col_num ++;
            }
            row.push_back(1);
            row_num ++;
            triangle.push_back(row);
        }
        return triangle;
    }

    void print_triangle () {
        vector<vector<int>> triangle = construct_pascal_triangle();
        //get the largest number
        const int k = n / 2;
        const int l = to_string(triangle[n-1][k-1]).length();
        int row_num = 1;
        for (vector<int> v:triangle) {
            for (int j=0; j<n-row_num; j++) {
                cout << string(l, ' ');
            }
            for (int i:v) {
                int i_length = to_string(i).length();
                cout << i << string(l+l-i_length, ' ');
            }
            cout << "\n";
            row_num ++;
        }
        return;
    }

};


int main() {
    Pascal_Triangle t(8);
    t.print_triangle();
}
