#include<bits/stdc++.h>

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

// 服が着れない日はない
// 同じ服を何回連続選でもいいし、1度も選ばない服があっても良い

int main(void)
{
  // input
  int D, N;     // 日数, 服の数
  cin >> D >> N;
  vector<int> T(D);   // 最高気温
  for(auto&& t: T)
    cin >> t;
  vector<int> A(N),B(N),C(N);   // 下限, 上限, 派手さ
  for(int ix=0; ix!=N; ++ix){
    cin >> A[ix] >> B[ix] >> C[ix];
  }
  /*
  dp[i][j]を、i日目にN[j]を来た時の求める値の最小値と定義する。
  i日目: ゼロオリジン
  j日目: ゼロオリジン
  このとき、i+1日目に着る服はdp[i][j]のN通りのみから決めることができる
  dp[i+1][j] = min(|C[j] - C[k]| + dp[i][k]) (0<=k<=N-1)
  */
  vector<vector<int>> dp(D, vector<int>(N, 0));

  // init XXX fixme
  for(int ix=0; ix!=N; ++ix){
    if(A[ix]<=T[0] && T[0]<=B[ix])
      dp[0][ix] = 0;
    else
      dp[0][ix] = -1;
  }

  // main
  for(int ix=0; ix<D-1; ++ix){      // day
    for(int jx=0; jx<N; ++jx){      // day[ix]に着る服
      if(A[jx]<=T[ix+1] && T[ix+1]<=B[jx]){   // 服jを着れる
        for(int kx=0; kx!=N; ++kx){           // 前日の服k
          if(dp[ix][kx]!=-1){                 // 前日にkを着ることが可能であれば
            dp[ix+1][jx] = max(dp[ix+1][jx], dp[ix][kx] + abs(C[jx] - C[kx]));
          }
        }
      }else{                                      // 服jを着れない
        dp[ix+1][jx] = -1;
      }
    }
  }

  // print
  //show2(dp);
  cout << *max_element(dp[D-1].begin(), dp[D-1].end()) << endl;
}