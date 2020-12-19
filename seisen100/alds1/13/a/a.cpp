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
/******** end of Utility ***************/

int k;

int main(void)
{
  // input
  int x,y;
  vector<vector<int>> board(8, vector<int>(8,0));
  cin >> k;
  for(int ix=0; ix!=k; ++ix){
    cin >> x >> y;
    board[x][y] = 1;
  }

  // main
}