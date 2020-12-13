
#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

#define PI 3.14159265359

using namespace std;

int main(void)
{
  int n,x,count=0;
  while(1==1){
    count = 0;
    cin >> n >> x;
    if(n==0 && x==0)
      break;
    for(int min=1; min<x/3 && min-2<x; ++min)
      for(int med=min+1; med<x-(min+med); ++med){
        if(x-(min+med) <= n){
          ++count;
        }
      }
    cout << count << endl;
  }
}