#include<bits/stdc++.h>

#define PI 3.14159265359

using namespace std;

template <class T>
using Graph = vector<vector<T>>;

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

/******** end of Utility ***************/

// G: Graph
// v: 次に訪れる頂点
// d: 最初に頂点を見つけたタイムスタンプ(行きがけ順)
//    -1で初期化されている必要がある
// f: ある頂点の隣接リストを探索し終えた時刻のタイムスタンプ(帰りがけ順)
//    -1で初期化されている必要がある
// timestamp: タイムスタンプ
// @return: vの隣接頂点の探索に要した時間
template<typename T>
void dfs(const Graph<T> &G, int v, vector<T> &d, vector<long> &f, T &timestamp)
{
  d[v] = timestamp++;
  for(auto next_v: G[v]){   // 隣接する頂点を探索
    if(d[next_v] != -1){  // 既に探索済み
      continue;
    }else{
      dfs(G, next_v, d, f, timestamp); // 次の頂点をDFS
    }
  }
  f[v] = timestamp++;
}

long n,k,u;
Graph<long> G;      // グラフ
vector<long> d;     // 頂点G[ix]を最初に発見した時刻
vector<long> f;     // vの隣接リストを調べ終えた時刻

int main(void)
{
  // input
  cin >> n;
  G.resize(n);
  d.assign(n, -1);
  f.assign(n, -1);
  for(auto&& g: G){
    cin >> u >> k;
    g.resize(k);
    for(auto&& _g: g){
      cin >> _g;
      --_g;               // 頂点はゼロオリジンに
    }
  };

  // main
  long timestamp = 1;
  for(int ix=0; ix!=n; ++ix){
    if(d[ix] == -1)
      dfs(G, ix, d, f, timestamp);
  }
  for(int ix=0; ix!=n; ++ix){
    cout << ix+1 << " " << d[ix] << " " << f[ix] << endl;
  }
}