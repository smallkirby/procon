#include<bits/stdc++.h>

#define PI 3.14159265359

using namespace std;

/******** Utility ***************/
int bsize(int bits, int _max){
  int c = 0;
  for(int ix=0; ix!=_max; ++ix)
    if((bits&(1<<ix)) !=0){
      ++c;
    }
  return c;
}

long factrial(long n){
  assert(n >= 0);
  if(n <= 1)
    return 1;
  long _sum = 1;
  for(int ix=0; ix!=(n-1); ++ix)
    _sum *= n-ix;
  return _sum;
}

template<typename T>
void show(vector<T> v)
{
  for(auto _v: v)
    cout << _v << " ";
  cout << endl;
}

template<typename T>
void show2(vector<vector<T>> v)
{
  for(auto __v: v){
    cout << "(";
    for(auto _v: __v){
      cout << _v << ", ";
    }
    cout << ")" << endl;
  }
}
/******** end of Utility ***************/

int main(void)
{
  // input
  long N;
  int n;
  long _sum = 0;
  cin >> N;
  vector<long> A(N);
  for(auto&& a: A)
    cin >> a;
  sort(A.begin(), A.end());

  for(int ix=N-1; ix>=0; --ix)
    _sum += ix*A[ix] - (N-1-ix)*A[ix];
  cout << _sum << endl;
}