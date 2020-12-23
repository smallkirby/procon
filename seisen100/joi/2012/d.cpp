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
  int N, K, tmp1, tmp2;        // total day, fixed days
  cin >> N >> K;
  /*
  0: トマト1連
  1: トマト2連
  2: クリーム1連
  3: クリーム2連
  4: バジル1連
  5: バジル2連
  */
  vector<vector<long>> dp(N, vector<long>(6, 0));
  vector<int> fixed_days(N, -1);
  for(int ix=0; ix!=K; ++ix){
    cin >> tmp1 >> tmp2;
    fixed_days[tmp1-1] = tmp2;
  }

  // init
  if(fixed_days[0] != -1){
    dp[0][(fixed_days[0]-1)*2] = 1;
  }else{
    dp[0][0] = 1;
    dp[0][2] = 1;
    dp[0][4] = 1;
  }

  // main
  long tmpsum, fmenu;
  for(int ix=0; ix<N-1; ++ix){      // ix: メニューが確定している日付
    if(fixed_days[ix+1] != -1){
      fmenu = fixed_days[ix+1] - 1;
      tmpsum = 0;
      for(int kx=0; kx!=6; ++kx){
        if(kx != fmenu*2 && kx != fmenu*2+1){
          tmpsum += dp[ix][kx] % 10000;
        }
      }
      dp[ix+1][fmenu*2] = tmpsum % 10000;
      dp[ix+1][fmenu*2 + 1] = dp[ix][fmenu*2] % 10000;

    }else{
      // トマト
      dp[ix+1][0] = (dp[ix][2] + dp[ix][3] + dp[ix][4] + dp[ix][5]) % 10000;
      dp[ix+1][1] = dp[ix][0] % 10000;
      // クリーム
      dp[ix+1][2] = (dp[ix][0] + dp[ix][1] + dp[ix][4] + dp[ix][5]) % 10000;
      dp[ix+1][3] = dp[ix][2] % 10000;
      // バジル
      dp[ix+1][4] = (dp[ix][0] + dp[ix][1] + dp[ix][2] + dp[ix][3]) % 10000;
      dp[ix+1][5] = dp[ix][4] % 10000;
    }
  }

  // print
  //show2(dp);
  long sum = 0;
  for(auto d: dp[N-1]){
    sum += d;
    sum %= 10000;
  }
  cout << sum << endl;
}