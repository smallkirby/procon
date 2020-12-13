#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

#define PI 3.14159265359

using namespace std;

int main(void)
{
  int n;
  cin >> n;
  vector<int> ns(n);
  for(int ix=0;ix!=n;++ix)
    cin >> ns.at(ix);
  for(int ix=ns.size()-1; ix>=0; --ix)
    if(ix!=0)
      cout << ns.at(ix) << " ";
    else
      cout << ns.at(ix) << endl;
}