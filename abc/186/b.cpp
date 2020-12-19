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
  long count = 0;
  long N;
  stringstream s8,s10;
  cin >> N;

  // main
  for(int ix=7; ix<=N; ++ix){
    s8.str("");
    s10.str("");
    s8 << oct << ix;
    s10 << dec << ix;
    if(s10.str().find("7")!=string::npos || s8.str().find("7")!=string::npos){
      ++count;
    }
  }
  cout << N - count << endl;
}