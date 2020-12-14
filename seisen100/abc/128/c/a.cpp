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
vector<int> k;
vector<vector<int>> s;
vector<int> p;
vector<int> S; // Sのbit表現 -> balbの状態とANDをとってmod=pならば点灯

// zero-origin
int vec2bit(vector<int> v)
{
  int s = 0;
  for(auto _v: v)
    s += 1<<(_v-1);
  return s;
}

void show(vector<int> v){
  for(auto _v: v){
    cout << _v << " ";
  }
  cout << endl;
}

bool check(int n, int q, int si)
{
  int c = 0;
  for(int ix=0; ix!=si; ++ix){
    if((n & (1<<ix)) != 0){
      ++c;
    }
  }
  return c%2 == q;
}

int main(void)
{
  int count = 0;
  cin >> N >> M;
  k.resize(M);
  s.resize(M);
  p.resize(M);
  S.resize(M);

  // input
  for(int ix=0;ix!=M;++ix){
    cin >> k[ix];
    s[ix].resize(k[ix]);
    for(auto&& _s: s[ix])
      cin >> _s;
  }
  for(auto&& _p: p){
    cin >> _p;
  }
  for(int ix=0; ix!=M; ++ix)
    S[ix] = vec2bit(s[ix]);

  //cout << "*********" << endl;
  //show(p);
  //show(S);
  //if(check(1,1,N))
  //  cout << "yes" << endl;
  //else
  //  cout << "no" << endl;
  //cout << "*********" << endl;

  // main
  int t = 0;
  for(int bits=0; bits!=1<<N; ++bits){
    bool found = true;
    //cout << "bits: "<<bits<<endl;
    for(int ix=0; ix!=M; ++ix){ // 各ランプ
      t = bits & S[ix];
      //cout <<"\tt:"<<t<<":"<<p[ix];
      if(!check(t, p[ix], N)){
        //cout << " FAIL" << endl;
        found = false;
        break;
      }
    }
    if(found){
      ++count;
      //cout << "!" << bits << endl;
    }
  }

  cout << count << endl;
}