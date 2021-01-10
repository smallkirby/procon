
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

auto a = vector<int>();  // 開始日
auto b = vector<int>();  // 終了日
auto c = vector<int>();  // 利用料/day
long N;

#define AAA(n,ix) a[ix]<=n&&n<=b[ix] ? c[ix] : 0

long cost(long dayn){
  long _sum = 0;
  for(int ix=0; ix<N; ++ix)
    _sum += AAA(dayn, ix);
  return _sum;
}

int main(void)
{
  // input
  long C;  // サービス個数・プラン利用料/day
  auto events = map<long,long>();  // イベント発生日・価格変動
  auto eventsday = vector<long>();
  cin >> N >> C;
  a.resize(N);
  b.resize(N);
  c.resize(N);
  for(int ix=0; ix!=N; ++ix){
    cin >> a[ix] >> b[ix] >> c[ix];
    if(events.find(a[ix])==events.end())
      events[a[ix]] = c[ix];
    else
      events[a[ix]] += c[ix];

    if(events.find(b[ix]+1)==events.end())
      events[b[ix]+1] = -1*c[ix];
    else
      events[b[ix]+1] += -1*c[ix];
  }

  long total = 0;
  long current_price = 0;
  long now = 1;
  long endday = *max_element(b.begin(),b.end());
  auto tomorrow = events.begin();
  for(auto it = events.begin(); it != events.end(); ++it){
    ++tomorrow;
    if(tomorrow == events.end() || now > endday)
      break;
    current_price += it->second;
    //cout <<it->first<<" "<<it->second<<" "<<total<<" "<<min(C,current_price)<<" "<<it->first<<"->"<<tomorrow->first<<endl;
    total += (tomorrow->first - it->first) * min(C, current_price);
  }

  cout << total << endl;
}