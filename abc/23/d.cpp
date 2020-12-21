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
    cout << ")" << endl
  }
}
/******** end of Utility ***************/

long N;
vector<long> H;
vector<long> S;
vector<double> F;

bool enable2shoot(long h)
{
  for(int ix=0; ix!=N; ++ix){
    F[ix] = (double)(h - H[ix]) / (double)S[ix]; // 高さhに達するまでの猶予時間
    if(F[ix] < 0)
      return false;
  }
  sort(F.begin(), F.end());

  for(int ix=0; ix!=N; ++ix){
    if(F[ix] < ix)
      return false;
  }
  return true;
}

int main(void)
{
  // input
  cin >> N;
  H.resize(N);
  S.resize(N);
  F.resize(N);
  for(int ix=0; ix!=N; ++ix){
    cin >> H[ix];
    cin >> S[ix];
    F[ix] = H[ix] + S[ix]*(N-1);
  }

  // main
  long minH = *min_element(H.begin(), H.end());
  long maxH = *max_element(F.begin(), F.end());
  long h;
  long last_ok_h;
  while(minH <= maxH){
    h = minH + (maxH - minH)/2;
    if(!enable2shoot(h)){
      minH = h + 1;
    }else{
      maxH = h - 1;
      last_ok_h = h;
    }
  }
  cout << last_ok_h << endl;
}