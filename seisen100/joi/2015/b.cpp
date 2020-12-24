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

vector<long> A;
vector<vector<long>> dp;
long N;
unsigned long num_func_called;

// A[l:r+1]まで残っている場合のJOIくんが取り得る最大値を返す(それまでに取った分はカウントしない)
long func(long l, long r, bool ioi_turn)
{
  if(dp[l%N][r%N] != -1){     // 既に探索済み。よってメモ化した値を使う
    return dp[l%N][r%N];
  }
  if(l == r){           // 最後の一切れ
    if(ioi_turn){
      dp[l%N][r%N] = 0;
      return 0;
    }else{
      dp[l%N][r%N] = A[l%N];
      return A[l%N];
    }
  }

  if(ioi_turn){   // IOIちゃんのターン
    if(A[l%N] > A[r%N]){    // 左端の方がでかい
      return dp[l%N][r%N] = func(l+1, r, false);   // 左端をとって再計算(取ったA[l]はIOIちゃんのだからカウントしない)
    }else{
      return dp[l%N][r%N] = func(l, r-1, false);
    }
  }else{          // JOIくんのターン
    return dp[l%N][r%N] = max(func(l+1, r, true) + A[l%N], func(l, r-1, true) + A[r%N]);    // 左端と右端を食べた場合でスコアの大きい方を選ぶ
  }
}

int main(void)
{
  // input
  cin >> N;
  vector<long> _A(N);
  for(auto&& a: _A)
    cin >> a;
  A.resize(2*N);
  A = _A;
  copy(A.begin(), A.end(), back_inserter(A));     // 円環だと参照しにくいから2個連結する. これで(N-1)+3番目にアクセスするときにはA[N-1+3]でいける

  // init
  /*
  A[i]からA[j]まで残っている場合のJOI君の最大値
  i>=jでもよい
  */
  dp.resize(N, vector<long>(N, -1));

  // main
  long tmp = -1;
  for(int ix=0; ix!=N; ++ix){     // A[ix]だけ取った状態でスタート
    //cout << ix+1<<"~"<<ix-1+N<<" eat="<<ix<<" "<<A[ix]<<endl;
    tmp = max(tmp, func(ix+1, ix+N-1, true) + A[ix]);
  }

  // print
  cout << tmp << endl;
}