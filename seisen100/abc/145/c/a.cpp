#include <iostream>
#include <vector>
#include <string>
#include<iomanip>
#include <cmath>
#include<algorithm>
#include<numeric>
#include<cassert>

#define PI 3.14159265359

using namespace std;

/******** Utility ***************/
#define max(a,b) (a<b ? b : a)
#define min(a,b) (a>b ? b : a)

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
/******** end of Utility ***************/

int N;
vector<vector<int>> xy;

int main(void)
{
  // input
  cin >> N;
  xy.resize(N);
  for(auto&& _xy: xy){
    _xy.resize(2);
    cin >> _xy[0] >> _xy[1];
  }
  vector<int> v(N);
  iota(v.begin(), v.end(), 0);

  // main
  double sumlen = 0;
  do{
    for(int ix=0; ix!=N-1; ++ix){
      sumlen += sqrt(pow(xy[v[ix]][0]-xy[v[ix+1]][0], 2) + pow(xy[v[ix]][1]-xy[v[ix+1]][1], 2));
    }
  }while(next_permutation(v.begin(), v.end()));
  //cout << sumlen << endl; // XXX

  //cout << factrial(10) << endl;
  cout << fixed << setprecision(10) << (double)(sumlen)/(double)(factrial(N)) << endl;
}