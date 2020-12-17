
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

long D; // 環状線の全長
long N; // 店舗数
vector<long> n; // 店舗住所
int m; // 注文数
vector<long> d; // 届け先

// 住所dへの最短移動距離を返す
long binsearch(long d)
{
  long left=0, right=N-1;
  long med;
  long smallest=__LONG_MAX__, sa;

  while(left <= right){
    med = left + (right - left)/2;
    sa = d - n[med];
    //cout << "n[med]:" << n[med] << " sa: " << sa << endl;
    if(sa == 0)
      return 0;
    else if(sa > 0){
      smallest = min(sa, smallest);
      left = med+1;
    }else{
      smallest = min(-1*sa, smallest);
      right = med-1;
    }
  }
  return min(smallest, abs(D-d));
}

int main(void)
{
  // input
  long count = 0;
  cin >> D;
  cin >> N;
  cin >> m;
  n.resize(N-1);
  d.resize(m);
  for(auto&& _n: n)
    cin >> _n;
  n.push_back(0); // 本店
  for(auto&& _d: d)
    cin >> _d;

  // main
  sort(n.begin(), n.end());

  for(auto _d: d)
    count += binsearch(_d);
  cout << count << endl;
}

//int main(void)
//{
//  // input
//  while(true){
//    long count = 0;
//    cin >> D;
//    if(D==0)
//      return 0;
//    cin >> N;
//    cin >> m;
//    n.resize(N-1);
//    d.resize(m);
//    for(auto&& _n: n)
//      cin >> _n;
//    n.push_back(0); // 本店
//    for(auto&& _d: d)
//      cin >> _d;
//
//    // main
//    sort(n.begin(), n.end());
//
//    for(auto _d: d)
//      count += binsearch(_d);
//    cout << count << endl;
//  }
//}