#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

#define PI 3.14159265359

using namespace std;

int main(void)
{
  vector<int> ns(4);
  int min=100;
  for(int ix=0;ix!=4;++ix)
    cin >> ns.at(ix);
  for(auto n: ns)
    min = n<min ? n : min;
  cout << min << endl;
}