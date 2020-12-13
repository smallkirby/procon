#include <iostream>
#include <vector>
#include <string>
#include<algorithm>

using namespace std;

int main(void)
{
  vector<int> ns(3);
  for(int ix=0;ix!=3;++ix)
    cin >> ns.at(ix);

  sort(ns.begin(), ns.end());

  for(int ix=0;ix!=3;++ix){
    cout << ns.at(ix);
    if(ix!=2)
      cout << " ";
    else
      cout << endl;
  }
}