#include <iostream>
#include <vector>
#include <string>
#include<iomanip>
#include <cmath>
#include<algorithm>

#define PI 3.14159265359

using namespace std;


#define max(a,b) (a<b ? b : a)
long sumvec(vector<long> v){
  long count = 0;
  for(auto a: v)
    count += a;
  return count;
}

int main(void)
{
  long N,M;
  cin >> N >> M;
  vector<vector<long>> A(N, vector<long>(M));
  vector<long> maxes(M*(M-1)/2);
  vector<long> temp(100);
  long tix;
  long count = 0;

  for(int ix=0; ix!=N; ++ix)
    for(int jx=0; jx!=M; ++jx)
      cin >> A[ix][jx];

  tix = 0;
  for(int ix=0; ix!=M-1; ++ix){
    for(int jx=ix+1; jx!=M; ++jx){ // 2曲選曲
      for(int kx=0; kx!=N; ++kx){ // 1人
        temp[kx] = max(A[kx][ix], A[kx][jx]);
      }
      maxes[tix] = sumvec(temp);
      ++tix;
    }
  }
  count = *max_element(maxes.begin(), maxes.end());
  cout << count << endl;
}