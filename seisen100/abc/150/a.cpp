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

int main(void)
{
  // input
  int a=-1,b=-1;
  int count = 0;
  cin >> N;
  vector<int> n(N);
  vector<int> m(N); // XXX
  vector<int> P(N), Q(N);
  iota(n.begin(), n.end(), 1);
  iota(m.begin(), m.end(), 1); // XXX
  for(auto&& p: P)
    cin >> p;
  for(auto&& q: Q)
    cin >> q;

  do{
    if(a==-1 && P==n)
      a = count;
    if(b==-1 && Q==n)
      b = count;
    if(a!=-1 && b!=-1)
      break;
    ++count;
  }while(next_permutation(n.begin(), n.end()));

  cout << std::abs(a-b) << endl;
}