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

long gcds(long a, long b, long c)
{
  assert(a>0 && b>0 && c>0);
  long hoge = min(min(a,b), c);
  long fuga;
  //cout << "fuga: "<<hoge<<endl;
  for(fuga = hoge; fuga>=1; --fuga){
    //cout << "-- " << a << " "<< b << " " << c << " " << fuga << endl;
    // %と&をtypoして無限時間とかしたけど...
    if(a%fuga==0 && b%fuga==0 && c%fuga==0){
      //cout <<"break: "<<fuga<<endl;
      break;
    }
  }
  return fuga;
}

// ax + by = gcd(a,b)
// 破壊的
long extgcd(long a, long b, long &x, long &y)
{
  if(a < b)
    return extgcd(b,a,y,x);
  if(b > 0){
    long g = extgcd(b, a%b, y, x);
    y -= (a/b) * x;
    return g;
  }else{
    x = 1;
    y = 0;
    return a;
  }
}


/******** end of Utility ***************/


int main(void)
{
  //cout << minextgcd(37, 10) << endl;
  //return 0;

  // input
  int T;
  long N, S, K;
  long nmod, smod, kmod, nowmod, samod;
    cin >> T;
  for(int t=0; t!=T; ++t){
    cin >> N >> S >> K;
    /*
    long count = 0;
    nowmod = S % K;
    nmod = N % K;
    samod = (N-S) % K;

    // modが変わらないなら-1
    if(nmod == 0 && samod != 0){
      cout << -1 << endl;
      continue;
    }
    // 同じmod上にいる
    if(nmod == 0){
      cout << (N-S) / K  - 1 << endl;
      continue;
    }




    // 同じmodにいない

    // まずは0~mod-1へ
    long L = K - N%K;
    count += (N-S)/K; // XXX
    nowmod = (nowmod + L) % K;
    if(nowmod == 0){
      cout << count << endl;
      continue;
    }
    bool found = false;
    // 同じmod上に乗りたい
    for(int ix=0; ix!=K; ++ix){
      nowmod = (nowmod + L)%K;
      count += N/K + 1;
      if(nowmod == 0){
        found = true;
        break;
      }
    }
    if(!found){
      cout << -1 << endl;
      continue;
    }else{
      cout << count << endl;
    }
    */

   // S + xK == 0 mod Nになるmin(x)を求める
   // つまり、Kx == N-S mod N なる最小のxが解
    //cout << "[+] "<< K << ":" << N-S << ":" << N << endl;
    long g = __gcd(K, __gcd(N-S, N));
    long k = K/g;
    long n = (N-S)/g;
    long m = N/g;
    // k*x == n mod m の min(x)
    if(__gcd(k,m)!=1){ // 解なし
      cout << -1 << endl;
    }else{  // 解あり: k*x==n modm <=> k(k^-1 * n) == n modm であるから、kのmについてのモジュラ逆数を求めればよい
      // 逆元は拡張ユークリッド互助法で
      long x=0,y=0;
      extgcd(k,m,x,y);
      //cout << ":" << x << ":" << m <<endl;
      //cout << ":" << (x+m)%m << endl;
      cout << ((x + m)%m *n) % m << endl;
    }
  }
}