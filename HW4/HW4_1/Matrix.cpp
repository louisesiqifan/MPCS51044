#include "Matrix.h"
#include <iostream>
#include <chrono>
using namespace mpcs51044;
using namespace std;

int main()
{
	Matrix<3, 3> m = {
			{ 1, 2, 3, },
			{ 4, 5, 6, },
			{ 7, 8, 9, }
	};
	Matrix<3, 3> result = m + m;
	cout << result;

	m += result;
	cout << m;
	return 0;
}
