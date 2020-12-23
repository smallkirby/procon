#include<bits/stdc++.h>

#define PI 3.14159265359
#define IMAX 1<<29

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
  /*
  今回は、「同じものを何回でも選ぶことができる」ということに注意
  */
  struct bag{
    int val;
  };

  // input
  int N, W;       // 硬貨の種類, 総額
  cin >> W >> N;
  vector<vector<int>> nup(N+1, vector<int>(W+1, -1));     // 0~限界まで. 荷物iまでを見た時にwと同じ値段のときの最小枚数
                                                          // これって超えること無いんかな???(ピッタリ払えない場合)
  vector<struct bag> B(N);
  for(int ix=0; ix!=N; ++ix){
    cin >> B[ix].val;
  }
  nup[0][0] = 0;
  for(int ix=0; ix!=N; ++ix){
    for(int jx=0; jx!=W+1; ++jx){
      if(ix==0 && jx==0)
        continue;
      nup[ix][jx] = IMAX;
    }
  }

  // main
  for(int n=0; n!=N; ++n){
    for(int w=0; w!=W+1; ++w){
      //cout <<"["<<n<<","<<w<<"] "<<nup[n][w-B[n].val]+1<<" or "<<nup[n][w]<<endl;
      if(w >= B[n].val)
        nup[n+1][w] = min(nup[n+1][w - B[n].val] + 1, nup[n][w]);
      else
        nup[n+1][w] = nup[n][w];
    }
  }

  // print
  cout << nup[N][W] << endl;
}