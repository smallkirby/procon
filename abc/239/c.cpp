#include<bits/stdc++.h>
#include <iomanip>

#define IMAX 1<<29
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
void show(vector<T> v, int maxrow)    // 適度に改行入れるver
{
  for(int ix=0; ix!=v.size(); ++ix){
    if(ix!=0 && ix%maxrow==0)
      cout << endl;
    cout << v[ix] << " ";
  }
  cout << endl;
}

template<typename T>
void show2(vector<vector<T>> v)
{
  int ix = 0;
  for(auto __v: v){
    cout << "[" << ix++ << "] (";
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

// G: Graph
// dist: startからの最小距離
// start: start地点
template<typename T>
void bfs(const Graph<T> &G, vector<int> &dist, const int start)
{
  // init
  queue<int> que;
  dist.assign(dist.size(), -1);
  dist[start] = 0;
  que.push(start);

  // BFS
  while(!que.empty()){
    int v = que.front();
    que.pop();
    for(auto next_v: G[v]){
      if(dist[next_v] != -1)  // 訪問済み
        continue;
      dist[next_v] = dist[v] + 1;
      que.push(next_v);
    }
  }
}

// グラフの周りに余白をつけていること前提
void genGraph(Graph<int> &G, vector<string> &board, int R, int C)
{
  for(int row=1; row!=R-1; ++row){
    for(int col=1; col!=C-1; ++col){
      if(board[row][col] == '#')
        continue;
      if(board[row-1][col] == '.')
        G[(row-1)*C + col].push_back(row*C + col);
      if(board[row][col-1] == '.')
        G[(row)*C + col-1].push_back(row*C + col);
      if(board[row][col+1] == '.')
        G[(row)*C + col+1].push_back(row*C + col);
      if(board[row+1][col] == '.')
        G[(row+1)*C + col].push_back(row*C + col);
    }
  }
}

/******** end of Utility ***************/

int main(void)
{
  // input
  long long x1, x2, y1, y2;
  cin >> x1 >> y1 >> x2 >> y2;

  // main
  const auto kyori = [](long long px1, long long py1, long long px2, long long py2) { return sqrt((pow((double)px1 - (double)px2, 2.0) + pow((double)py1 - (double)py2, 2.0)));};
  cout << fixed;

  const auto chuten_x = (double)(x1 + x2) / 2.0;
  const auto chuten_y = (double)(y1 + y2) / 2.0;

  const auto begin_x = ceil(chuten_x - 5);
  const auto begin_y = ceil(chuten_y - 5);

  for (int ix_x = 0; ix_x < 10; ++ix_x) {
    for (int ix_y = 0; ix_y < 10; ++ix_y) {
      const auto  kyori1 = kyori(x1, y1, begin_x + ix_x, begin_y + ix_y);
      const auto kyori_2 = kyori(x2, y2, begin_x + ix_x, begin_y + ix_y);
      //cout << begin_x + ix_x << " " << begin_y + ix_y << endl;
      //cout << kyori1 << " " << kyori_2 << endl;
      if (kyori1 == kyori_2) {
        if (kyori1 == sqrt(5.0)) {
          cout << "Yes" << endl;
          return 0;
        }
      }
    }
  }

  // print
  cout << "No" << endl;
  return 0;
}
