#include"LockFreeStack.h"
#include<iostream>
using namespace std;
using namespace mpcs51044;

int main()
{
  Stack ls;
  ls.push(1);
  ls.push(3);
  ls.push(5);
  for (int i = 0; i < 3; i++)
    cout << ls.pop() << endl;
  return 0;
}
