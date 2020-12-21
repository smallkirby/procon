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

void genGraph(Graph<int> &G, vector<string> &board, int R, int C)
{
  for(int row=1; row!=R; ++row){
    for(int col=1; col!=C; ++col){
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

void _genGraph(Graph<int> &G, const vector<vector<int>> &B, const int R, const int C)
{
  for(int row=1; row!=R-1; ++row){
    for(int col=1; col!=C-1; ++col){
      if(B[row][col] == 1)
        continue;
      if(B[row-1][col] == 0)
        G[(row-1)*C + col].push_back(row*C + col);
      if(B[row][col-1] == 0)
        G[(row)*C + col-1].push_back(row*C + col);
      if(B[row][col+1] == 0)
        G[(row)*C + col+1].push_back(row*C + col);
      if(B[row+1][col] == 0)
        G[(row+1)*C + col].push_back(row*C + col);
    }
  }
}

int main(void)
{
  // input
  int H,W;        // <=50
  int total_white = 0;
  cin >> H >> W;
  vector<vector<int>> B(H+2, vector<int>(W+2, 0));   // 余白は黒にしておく
  vector<string> tmp(H);
  for(int col=0; col!=W+2; ++col){
    B[0][col] = 1;
    B[H+1][col] = 1;
  }
  for(int row=0; row!=H; ++row){
    B[row+1][0] = 1;
    B[row+1][W+1] = 1;
    cin >> tmp[row];
    for(int col=0; col!=W; ++col){
      if(tmp[row][col] == '.'){
        B[row+1][col+1] = 0;
        ++total_white;
      }else
        B[row+1][col+1] = 1;
    }
  }

  // main
  /*
  結局は、最短でゴールした時が、一番黒塗りできるスペースが大きいわけだから、ただの最短経路問題じゃん???
  */
  Graph<int> G((H+2)*(W+2));
  vector<int> dist((H+2)*(W+2));
  _genGraph(G, B, H+2, W+2);
  bfs(G, dist, 1*(W+2)+1);

  // print
  if(dist[H*(W+2)+W] == -1)
    cout << -1 << endl;
  else
    cout << total_white - (dist[H*(W+2) + W] + 1) << endl;

  return 0;
}