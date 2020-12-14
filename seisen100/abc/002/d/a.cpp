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

int N,M;
vector<int> xy;

/*
0 ~ (1<<N)-1のビットで全派閥のパターンを表す
それぞれについて
  bitが1ならばMを全探索してそのbitで表される関係を調べる
  調べて、お相手となるbitをONにしたbitsを作成する。
  このbitsを派閥を表すbitsとANDして、
*/

int bsize(int bits, int _max){
  int c = 0;
  for(int ix=0; ix!=_max; ++ix)
    if((bits&(1<<ix)) !=0){
      ++c;
      //cout << (bits&(1<<ix)) << endl;
    }
  return c;
}

int main(void)
{
  // input
  int x,y,tmp;
  int nmax = 1;
  cin >> N >> M;
  if(M==0){
    cout << 1 << endl;
    return 0;
  }
  xy.resize(M);
  for(int ix=0; ix!=M; ++ix){
    cin >> x >> y;
    xy[x-1] |= (1<<(y-1));
    xy[y-1] |= (1<<(x-1));
  }

  //cout << "*********" << endl;
  //cout << bsize(0b10111, 5) << endl;;
  //cout << "*********" << endl;
  //return 0;

  // main
  for(int bits=1; bits<(1<<N); ++bits){ // 2**N: 有る派閥において
    bool ok = true;
    for(int ix=0; ix!=N; ++ix){ // N:  各人が他の人と知り合いかどうかを調べる
      if((bits&(1<<ix)) != 0){
        if((xy[ix] & bits) != (bits^(1<<ix))){
          ok = false;
          break;
        }
      }
    }
    if(ok){
      tmp = bsize(bits, N);
      nmax = tmp>nmax ? tmp : nmax;
    }
  }

  cout << nmax << endl;
}