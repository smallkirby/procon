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

/******** end of Utility ***************/

int w,h;    // 陸と海の数
vector<vector<int>> c;
Graph<int> G;


template<typename T>
void genGraph(Graph<T> &G, int h, int w)
{
  int ix;
  for(int hx=0; hx!=h; ++hx){
    for(int wx=0; wx!=w; ++wx){
      ix = hx*w + wx;
      //cout << "-- "<<ix << ": " << c[hx][ix] << " = " << c.size() << endl;
      if(c[hx][wx] == 0)
        continue;

      if(1<=hx && 1<=wx && c[hx-1][wx-1]==1)
        G[ix].push_back((hx-1)*w + (wx-1));
      if(1<=hx && c[hx-1][wx]==1)
        G[ix].push_back((hx-1)*w + wx);
      if(1<=hx && wx<w-1 && c[hx-1][wx+1]==1)
        G[ix].push_back((hx-1)*w + (wx+1));

      if(1<=wx && c[hx][wx-1]==1)
        G[ix].push_back(hx*w + (wx-1));
      if(wx<w-1 && c[hx][wx+1]==1)
        G[ix].push_back(hx*w + (wx+1));

      if(hx<h-1 && 1<=wx && c[hx+1][wx-1]==1) // XXX
        G[ix].push_back((hx+1)*w + (wx-1));
      if(hx<h-1 && c[hx+1][wx]==1)
        G[ix].push_back((hx+1)*w + (wx));
      if(hx<h-1 && wx<w-1 && c[hx+1][wx+1]==1)
        G[ix].push_back((hx+1)*w + (wx+1));
    }
  }
}

int main(void)
{
  while(true){
    // input
    cin >> w >> h;
    if(h==0 && w==0)
      break;
    vector<int> d(h*w, -1), f(h*w, -1);
    c.assign(h, vector<int>(w, 0));
    G.clear();
    G.resize(h*w);
    for(auto&& _h: c){
      for(auto&& _w: _h){
        cin >> _w;
      }
    }
    genGraph(G, h, w);

    // main
    long count = 0;
    int timestamp;
    for(int ix=0; ix!=h*w; ++ix){ // 連結成分数のカウント
      if(d[ix] != -1)
        continue;
      if(c[ix/w][ix%w] == 1){
        dfs(G, ix, d, f, timestamp);
        ++count;
      }
    }

    cout << count << endl;
  }
}