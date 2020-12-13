#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

#define PI 3.14159265359

using namespace std;

int main(void)
{
  int n, max=-1000000, min=+1000000;
  long sum=0;
  cin >> n;
  vector<int> ns(n);
  for(int ix=0;ix!=n;++ix)
    cin >> ns.at(ix);
  for(auto n: ns){
    sum += n;
    max = max<n ? n : max;
    min = min>n ? n : min;
  }
  cout << min << " " << max << " " << sum << endl;
}