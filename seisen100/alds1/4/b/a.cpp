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

void show(vector<int> v)
{
  for(auto _v: v)
    cout << _v << " ";
  cout << endl;
}

void show2(vector<vector<int>> v)
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

long n,q;
vector<long> S,T;

long binsearch(long num)
{
  long left=0, med, right=n-1;

  while(right >= left){
    med = left + (right - left)/2;
    if(S[med] == num)
      return med;
    else if(S[med] > num)
      right = med - 1;
    else
      left = med + 1;
  }
  return -1;
}

int main(void)
{
  long count = 0;
  cin >> n;
  S.resize(n);
  for(auto&& s: S) // ソート済み
    cin >> s;

  cin >> q;
  T.resize(q);
  for(auto&& t: T)
    cin >> t;

  // main
  for(auto _t: T){
    if(binsearch(_t) != -1)
      ++count;
  }
  cout << count << endl;
}