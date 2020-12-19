
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

/* 概要
開始時1個割る。
以降は毎秒割る。この時の高度がペナルティ。
最終的な得点はペナルティの最大値。
得点を最小化したい。
*/

int N; // 風船の個数
vector<long> H, S; // 高度初期値・高度上昇度

int main(void)
{
  // input
  cin >> N;
  H.resize(N);
  S.resize(N);
  for(int ix=0; ix!=N; ++ix){
    cin >> H[ix] >> S[ix];
  }

  // main

}