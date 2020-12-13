#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

#define PI 3.14159265359

using namespace std;

int main(void)
{
  int n,m;
  cin >> n;

  for(int ix=1; ix<=n; ++ix){
    if(ix%3 == 0){
      cout << " " << ix;
      continue;
    }
    m = ix;
    while(m>0){
      if(m%10 == 3){
        cout << " " << ix;
        break;
      }
      m /= 10;
    }
  }
  cout << endl;
}