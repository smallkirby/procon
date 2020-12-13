
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

int main(void)
{
  int N,n;
  cin >> N;
  int count = 0;
  for(int ix=1; ix<=N; ix+=2)
    if(count_prime(ix)==8)
      ++count;
  cout << count << endl;
}