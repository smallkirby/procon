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


// 実装重いって書いてたけど、全然そうでもなくね??
void _bfs(vector<vector<int>> &data, vector<int> &dist, int h, int w)
{
  // init
  queue<int> que;
  pair<int,int> cur(0,0);
  dist.assign(dist.size(), -1);
  dist[cur.first*w + cur.second] = 0;
  que.push(cur.first*w + cur.second);

  // BFS
  while(!que.empty()){
    int v = que.front();
    que.pop();
    cur = pair<int,int>(v/w, v%w);

    if(cur.first>=1 && dist[(cur.first-1)*w + (cur.second)]==-1 && data[cur.first*2-1][cur.second*2]!=1){
      dist[(cur.first-1)*w + (cur.second)] = dist[v] + 1;
      que.push((cur.first-1)*w + (cur.second));
    }
    if(cur.second>=1 && dist[(cur.first)*w + (cur.second-1)]==-1 && data[cur.first*2][cur.second*2-1]!=1){
      dist[(cur.first)*w + (cur.second-1)] = dist[v] + 1;
      que.push((cur.first)*w + (cur.second-1));
    }
    if(cur.second<w-1 && dist[(cur.first)*w + (cur.second+1)]==-1 && data[cur.first*2][cur.second*2+1]!=1){
      dist[(cur.first)*w + (cur.second+1)] = dist[v] + 1;
      que.push((cur.first)*w + (cur.second+1));
    }
    if(cur.first<h-1 && dist[(cur.first+1)*w + (cur.second)]==-1 && data[cur.first*2+1][cur.second*2]!=1){
      dist[(cur.first+1)*w + (cur.second)] = dist[v] + 1;
      que.push((cur.first+1)*w + (cur.second));
    }
  }
}

int main(void)
{
  // input
  int w,h;
  while(true){
    cin >> w >> h;
    if(w==0 && h==0)
      break;
    vector<vector<int>> data(h*2-1, vector<int>(w*2-1, -1));    // (x,y)から(w,z)にいけるかどうかは、data[y+z][x+w]をみればよい
    for(int ix=0; ix!=h*2-1; ++ix){
      for(int jx=0; jx!=w*2-1; ++jx){
        if(ix%2==0){    // 縦の壁データ
          if(jx%2==0)
            continue;
          cin >> data[ix][jx];
        }else{          // 横の壁のデータ
          if(jx%2==1)
            continue;
          cin >> data[ix][jx];
        }
      }
    }

    // main
    vector<int> dist(h*w, -1);
    _bfs(data, dist, h, w);

    // print
    cout << dist[h*w-1]+1 << endl;
  }
}