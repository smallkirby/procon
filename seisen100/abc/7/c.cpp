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

/******** end of Utility ***************/

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

int main(void)
{
  // input
  int R, C;     // row, col
  int start_row, start_col, goal_row, goal_col;
  cin >> R >> C;
  cin >> start_row >> start_col;
  cin >> goal_row >> goal_col;
  --start_col; --start_row; --goal_col; --goal_row;
  Graph<int> G(R*C);
  vector<string> board(R);
  for(auto&& row: board){
    cin >> row;
  }

  // main
  if(R <= 2 || C <= 2){
    cout << -1 << endl;
    return 0;
  }

  vector<int> dist(R*C, -1);
  genGraph(G, board, R, C);
  bfs(G, dist, start_row*C + start_col);

  // print
  cout << dist[goal_row*C + goal_col] << endl;
}