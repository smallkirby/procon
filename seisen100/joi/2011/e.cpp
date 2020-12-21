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

void genGraph(Graph<int> &G, vector<string> &board, int R, int C, vector<pair<int, int>> &factory, pair<int,int> &start)
{
  char t;
  for(int row=1; row!=R; ++row){
    for(int col=1; col!=C; ++col){
      if(board[row][col] == 'X')
        continue;
      else if(board[row][col] == 'S')
        start = pair<int,int>(row, col);
      else if(board[row][col] != '.'){
        //cout << "!"<<board[row][col]<<"!(" <<row<<","<<col<<")"<< endl;
        factory[board[row][col] - 0x30 - 1] = pair<int,int>(row, col);
      }

      if(board[row-1][col] != 'X')
        G[(row)*C + col].push_back((row-1)*C + col);
      if(board[row][col-1] != 'X')
        G[(row)*C + col].push_back(row*C + col-1);
      if(board[row][col+1] != 'X')
        G[(row)*C + col].push_back(row*C + col+1);
      if(board[row+1][col] != 'X')
        G[(row)*C + col].push_back((row+1)*C + col);
    }
  }
}

// 結局は、硬さ1のチーズから順番にチーズを食べていく最短経路を求めればいいだけ。
int main(void)
{
  // input
  int H, W, N;
  cin >> H >> W >> N;
  vector<string> board(H+2);    // 区域外は障害物と見做す
  for(int ix=0; ix!=W+2; ++ix){
    board[0].push_back('X');
    board[H+1].push_back('X');
  }
  for(int row=0; row!=H; ++row){
    cin >> board[row+1];
    board[row+1] = "X" + board[row+1] + "X";
  }
  //cout << "!"<<board[0][0]<<"!"<<endl;
  //show(board, 1);

  // main
  Graph <int> G((H+2)*(W+2));
  vector<pair<int, int>> factory(N);      // 硬さ順
  pair<int, int> start;
  genGraph(G, board, H+2, W+2, factory, start);
  //show2(G);

  //cout << "start: "<<start.first<<","<<start.second<<endl;
  //for(int ix=0; ix!=N; ++ix)
  //  cout << "fact: "<<factory[ix].first<<","<<factory[ix].second<<endl;

  // 1<=N<=9だし、9回くらいなら全部についてBFSしてもええやろ
  long counter = 0;
  for(int ix=0; ix!=N; ++ix){
    vector<int> dist((H+2)*(W+2));
    if(ix == 0){    // start
      bfs(G, dist, start.first * (W+2) + start.second);
    }else{    // 工場から出発
      bfs(G, dist, factory[ix-1].first * (W+2) + factory[ix-1].second);
    }
    counter += dist[factory[ix].first * (W+2) + factory[ix].second];
    //show(dist, W+2);
  }

  // print
  cout << counter << endl;
}