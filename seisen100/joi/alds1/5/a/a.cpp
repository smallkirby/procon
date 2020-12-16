#include <iostream>
#include <vector>
#include<algorithm>

#define PI 3.14159265359

using namespace std;

#define max(a,b) (a<b ? b : a)
#define min(a,b) (a>b ? b : a)
#define abs(n) ((n)>=0 ? (n) : -1*(n))

int n,q;
vector<long> A;
vector<long> m(q);

// これもbit全探索の考え方なのかな
bool func(int i, int _sum){
  if(_sum == 0)
    return true;
  if(i >= n)
    return false;
  return func(i+1, _sum) || func(i+1, _sum-A[i]);
}

int main(void)
{
  cin >> n;
  A.resize(n);
  for(auto&& a: A)
    cin >> a;
  cin >> q;
  m.resize(q);
  for(auto&& _m: m)
    cin >> _m;

  /*  時間足りなかった(0.5秒分くらい)
  // 探索範囲を絞るためにソート
  sort(A.begin(), A.end());

  for(int ix=0; ix!=q; ++ix){
    bool exist = false;
    // 最初に上限を決めちゃう
    int kx=0,_max=0,_min=0;
    for(kx=0;kx!=n;++kx){
      if(A[kx] >= m[ix])
        break;
    }
    // ビット全探索
    for(int bit=0; bit<(1<<kx); ++bit){ //O(2**n)
      int sum = 0;
      for(int jx=0; jx!=kx; ++jx){
        if(bit & (1<<jx))
          sum += A[jx];
      }
      if(sum == m[ix]){
        exist = true;
        break;
      }
    }
    if(exist)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
  */
  for(int ix=0;ix!=q;++ix)
    if(func(0, m[ix]))
      cout << "yes" << endl;
    else
      cout << "no" << endl;
}