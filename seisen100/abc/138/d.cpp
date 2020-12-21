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

int N,Q;        // 頂点数, 操作回数
vector<int> counter;    // カウンタ
vector<int> x, p;       // 操作対象, 追加カウンタ
Graph<int> G;   // グラフ

// ルート方向の枝に対しては進んじゃいけないが、その判断ってどうやってやるんだろう
// 取り敢えず全部の枝に対してDFSをして、ルートを発見したらtrueを返すようにしておこう
template<typename T>
bool dfs_add_counter(const Graph<T> &G, int v, vector<T> &d, vector<T> &f, T &timestamp, int adder, bool is_subroot)
{
  int tmp;

  if(v==0 && !is_subroot)
    return true;

  d[v] = timestamp++;
  for(auto next_v: G[v]){   // 隣接する頂点を探索
    if(d[next_v] != -1){  // 既に探索済み
      continue;
    }else{
      tmp = dfs_add_counter(G, next_v, d, f, timestamp, adder, false);
      if(tmp && is_subroot)
        continue;
      else if(tmp)
        return true;
    }
  }

  f[v] = timestamp++;
  counter[v] += adder;
  return false;
}

template<typename T>
void dfs_answer(const Graph<T> &G, int v, vector<T> &d, vector<T> &f, T &timestamp, int adder)
{
  //show(d);
  //cout << "   timestamp: " << timestamp << endl;
  d[v] = timestamp++;
  //show(d);
  //cout << "    " << v << "[" << counter[v] << "] <--- " << adder << endl;
  counter[v] += adder;
  for(auto next_v: G[v]){   // 隣接する頂点を探索
    if(d[next_v] != -1){  // 既に探索済み
      continue;
    }else{
      dfs_answer(G, next_v, d, f, timestamp, counter[v]);
    }
  }
  f[v] = timestamp++;
}


int main(void)
{
  // input
  int a,b;
  cin >> N >> Q;
  counter.assign(N, 0);
  G.resize(N);
  x.resize(Q);
  p.resize(Q);
  for(int ix=0; ix!=N-1; ++ix){
    cin >> a >> b;
    G[a-1].push_back(b-1);  // ゼロオリジン
    G[b-1].push_back(a-1);
  }
  for(int ix=0; ix!=Q; ++ix){
    cin >> p[ix] >> x[ix];
    --p[ix];
    counter[p[ix]] += x[ix];
  }

  // main
  // 普通に各jに対してDFSをしていたらTLEになってしまった。
  // 各ノードに対してその部分木をメモ化するようにするか??
  /*
  解答見ちゃった。
  たしかになァァァァ。与えられたp[j]にだけ最初カウンタを入れてやって、ルートから順に伝播させていけば良いのかぁぁぁぁ。
  */
  vector<int> d(N),f(N);
  int timestamp = 0;
  d.assign(N, -1);
  f.assign(N, -1);
  //int root_direction;
  //cout << " COUNTER " << endl;
  //show(counter);
  dfs_answer(G, 0, d, f, timestamp, 0);

  // print
  for(int ix=0; ix!=N; ++ix){
    cout << counter[ix];
    if(ix != N-1)
      cout << " ";
    else
      cout << endl;
  }
}