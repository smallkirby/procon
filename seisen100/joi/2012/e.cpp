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

void genGraph(Graph<int> &G, vector<vector<int>> &board, int R, int C, vector<bool> &is_building)
{
  int t;
  for(int row=0; row!=R; ++row){
    for(int col=0; col!=C; ++col){
      t = board[row][col];
      if(t == 1){     // 見てるのは建物
        is_building[row*C + col] = true;
      }
      if(row%2==0){   // 偶数
        if(row>=1 && col>=1 && board[row-1][col-1] == t)
          G[row*C + col].push_back((row-1)*C + (col-1));
        if(row>=1 && board[row-1][col] == t)
          G[row*C + col].push_back((row-1)*C + (col));
        if(col>=1 && board[row][col-1] == t)
          G[row*C + col].push_back((row)*C + (col-1));
        if(col<C-1 && board[row][col+1] == t)
          G[row*C + col].push_back((row)*C + (col+1));
        if(row<R-1 && 1<=col && board[row+1][col-1] == t)
          G[row*C + col].push_back((row+1)*C + (col-1));
        if(row<R-1 && board[row+1][col] == t)
          G[row*C + col].push_back((row+1)*C + (col));
      }else{          // 奇数
        if(row>=1 && board[row-1][col] == t)
          G[row*C + col].push_back((row-1)*C + (col));
        if(row>=1 && col<C-1 && board[row-1][col+1] == t)
          G[row*C + col].push_back((row-1)*C + (col+1));
        if(col>=1 && board[row][col-1] == t)
          G[row*C + col].push_back((row)*C + (col-1));
        if(col<C-1 && board[row][col+1] == t)
          G[row*C + col].push_back((row)*C + (col+1));
        if(row<R-1 && board[row+1][col] == t)
          G[row*C + col].push_back((row+1)*C + (col));
        if(row<R-1 && col<C-1 && board[row+1][col+1] == t)
          G[row*C + col].push_back((row+1)*C + (col+1));
      }
    }
  }
}

template<typename T>
void bfs_count(const Graph<T> &G, vector<int> &dist, const int start, int &counter, int H, int W, vector<bool> &is_building)
{
  // init
  queue<int> que;
  dist.assign(dist.size(), -1);
  dist[start] = 0;
  que.push(start);
  //cout << "(" << start << ": " << (int)(start/W) << "," << start%W << ") " << 6-G[start].size() << endl;
  counter += 6 - G[start].size();

  // BFS
  while(!que.empty()){
    int v = que.front();
    que.pop();
    for(auto next_v: G[v]){
      if(dist[next_v] != -1)  // 訪問済み
        continue;
      dist[next_v] = dist[v] + 1;
      que.push(next_v);

      //cout << "(" << next_v << ": " << (int)(next_v/W) << "," << next_v%W << ") " << 6-G[next_v].size() << endl;
      counter += 6 - G[next_v].size();
    }
  }
  //counter -= W*2*2 + H*2;   // 余白の周を引く
  counter -= W*2*2 + H*2 + (H-1)*2;   // 余白の周を引く
}

/*
建物島の個数と、それらが形成する閉路の個数を調べたい。
ということは、建物の連結の他に、外の連結塊もカウントして、その週の長さを引けば良いのかな
- 各ノードから探索開始(DFSでもBFSでもよさそう)
- 一度訪れたところは探索しない
- 探索開始座標をインデックスとして、その週の長さを保持
  - タイムリミット10secで、100x100以下だから、そんなに時間は気にしなくて良さそう

解説の考え方見ちゃった。
余白を作って塗りつぶし問題に帰着する。
*/
int main(void)
{
  // input
  int W,H;
  cin >> W >> H;
  vector<vector<int>> board(H+2, vector<int>(W+2, 0));
  vector<bool> is_building((H+2)*(W+2), false);
  Graph<int> G((H+2)*(W+2));
  board[0] = vector<int>(W+2, 0);
  board[H+1] = vector<int>(W+2, 0);
  for(int row=0; row!=H; ++row){
    for(int col=0; col!=W; ++col){
      cin >> board[row+1][col+1];
    }
  }

  //cout << "*****************" << endl;
  //show2(board);

  // main
  genGraph(G, board, H+2, W+2, is_building);
  //show2(G);
  vector<int> dist((H+2)*(W+2), -1);
  int counter = 0;
  bfs_count(G, dist, 0, counter, H+2, W+2, is_building);

  // print
  //show(dist, W+2);
  cout << counter << endl;
}