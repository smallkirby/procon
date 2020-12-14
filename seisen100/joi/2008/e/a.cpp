#include <iostream>
#include <vector>
#include <string>
#include<iomanip>
#include <cmath>
#include<algorithm>

#define PI 3.14159265359

using namespace std;

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

int R, C;
vector<vector<int>> A;

int col2int(int c){
  int _sum = 0;
  for(int ix=0; ix!=R; ++ix){
    _sum += A[ix][c]==1 ? (1<<ix) : 0;
  }
  return _sum;
}

void show(vector<int> v)
{
  for(auto _v: v)
    cout << _v << " ";
  cout << endl;
}

int main(void)
{
  // input
  int min_penalty = 10000*10;
  int tmp,num;
  cin >> R >> C;
  A.resize(R);
  for(auto&& a: A)
    a.resize(C);
  for(int ix=0; ix!=R; ++ix){
    for(auto&& c: A[ix]){
      cin >> c;
    }
  }

  //for(int ix=0; ix!=R; ++ix)
  //  show(A[ix]);
  //cout << col2int(0) << endl;
  //cout << col2int(1) << endl;
  //cout << col2int(2) << endl;
  //return 0;

  // main
  /*
  単純に考えると、黒を多くする行と白を多くする行を決め打ちして全探索するのかなぁ
  */
  for(int bits=0; bits<(1<<R); ++bits){ // 2**R: 1になってるところが黒(1)を多くする行
    int penalty = 0;
    //cout << bits << endl; // XXX
    for(int c=0; c!=C; ++c){ // C: 各columnをチェック
      tmp = col2int(c);
      num = bsize(~(bits^tmp), R); // num==そのままで良い数
    //  cout << "\t" << tmp << ":" << num << endl; // XXX
      penalty += num > R/2 ? R-num : num; // そのまま : ひっくり返し
    }
    //cout << "   " << penalty << endl; // XXX
    if(min_penalty > penalty)
      min_penalty = penalty;
  }

  cout << (R*C - min_penalty) << endl;
}