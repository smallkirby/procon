
#include <iostream>
#include <vector>
#include <string>
#include<iomanip>
#include <cmath>

#define PI 3.14159265359

using namespace std;

int count_prime(int N){
  int n= sqrt(N);
  int count = 0;
  for(int ix=1; ix<=n; ++ix)
    if(N%ix==0)
      count += 2;
  if(n*n == N)
    --count;
  return count;
}

bool acgt(size_t c){
  if(c=='A' || c=='C' || c=='G' || c=='T')
    return true;
  else
    return false;
}

int main(void)
{
  string S;
  cin >> S;
  int max = 0;
  int cur = 0;
  for(int ix=0; ix!=S.size(); ++ix){
    if(acgt(S.at(ix)))
      ++cur;
    else{
      max = max<cur ? cur : max;
      cur = 0;
    }
  }
  max = max<cur ? cur : max;
  cout << max << endl;
}