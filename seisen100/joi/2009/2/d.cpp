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

// G: Graph
// v: 次に訪れる頂点
// d: 最初に頂点を見つけたタイムスタンプ(行きがけ順)
//    -1で初期化されている必要がある
// f: ある頂点の隣接リストを探索し終えた時刻のタイムスタンプ(帰りがけ順)
//    -1で初期化されている必要がある
// timestamp: タイムスタンプ
// @return: vの隣接頂点の探索に要した時間
template<typename T>
void dfs(const Graph<T> &G, int v, vector<T> &d, vector<T> &f, T &timestamp)
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

/******** end of Utility ***************/

int m,n;    // mxn区画。<=90だから、スタート地点は全探索で大丈夫そう。
int max_counter=0;

void func(vector<vector<int>> &area, int row, int col, int counter) // xとy間違えちゃった...。xはrow、yはcolになってる
{
  int x = row, y = col;
  bool north = area[x][y-1] == 1;
  bool weast = area[x-1][y] == 1;
  bool east = area[x+1][y] == 1;
  bool south = area[x][y+1] == 1;
  area[x][y] = 0;     // 氷を割る

  if(north)
    func(area, x, y-1, counter+1);
  if(weast)
    func(area, x-1, y, counter+1);
  if(east)
    func(area, x+1, y, counter+1);
  if(south)
    func(area, x, y+1, counter+1);

  area[x][y] = 1;   // 氷を戻す
  if(counter+1 > max_counter){
    max_counter = counter+1;
  }
}

int main(void)
{
  // input
  cin >> m >> n;
  vector<vector<int>> area(m+2, vector<int>(n+2, 0)); // 区域外の1マスはあらかじめ0にしておく。
  for(int ix=0; ix!=m; ++ix){
    for(int jx=0; jx!=n; ++jx){
      cin >> area[ix+1][jx+1];
    }
  }

  // main
  for(int row=1; row!=m+1; ++row){
    for(int col=1; col!=n+1; ++col){
      if(area[row][col] == 1)
        func(area, row, col, 0);
    }
  }

  cout << max_counter << endl;
}