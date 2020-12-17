
#include<bits/stdc++.h>

#define PI 3.14159265359

using namespace std;

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

void show2(vector<vector<int>> v)
{
  for(auto __v: v){
    cout << "(";
    for(auto _v: __v){
      cout << _v << ", ";
    }
    cout << ")" << endl;
  }
}
/******** end of Utility ***************/

long N;
vector<long> A,B,C;

long binaryIndex(long key, vector<long> &v){
  long left=0, right=N-1, med;
  while(right>=left){
    med = left + (right-left)/2;
    if(v[med] == key)
      return med;
    else if(v[med] > key)
      right = med-1;
    else if(v[med] < key)
      left = med+1;
  }
  return -1;
}

int main(void)
{
  long count = 0;
  cin >> N;
  A.resize(N);
  B.resize(N);
  C.resize(N);
  for(auto&& a: A)
    cin >> a;
  for(auto&& b: B)
    cin >> b;
  for(auto&& c: C)
    cin >> c;

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  sort(C.begin(), C.end());
  vector<long>::iterator c_cur = C.begin();
  vector<long> memo(N, -1);
  vector<long> memoc(N, -1);
  long tmp = 0, tmpc = 0;
  long prev_b_bound = -1, prev_b_count = 0;

  /*
  // 普通にやったら0.2sec位TLEしたから、一部をBの値についてメモ化してみようか
  // それでも駄目だったから、Bが決まったの時点でB以下の組み合わせ数は固定なわけで、それごとメモ化
  // ついでに枝切り
  // これで26/32AC。殆どで0.8sec以下なのに一部で2sec以上が有るから、切れてない枝が有るか??
  // Cについてもメモ化してしまうべきか
  // うーん、27/32AC。コレ以上どうしたらええねん。
  for(auto a: A){   // N
    if(prev_b_bound > a){
      count += prev_b_count;
      continue;
    }

    auto b_bound = upper_bound(B.begin(), B.end(), a); // log2(N)
    tmp = b_bound - B.begin();
    prev_b_bound = *b_bound;
    if(tmp >= N)
      continue;
    if(memo[tmp] == -1){ // メモにないから計算
      memo[tmp] = 0;
      for(; b_bound != B.end(); ++b_bound){ // N: Bのメモカ
        if(*(C.end()-1) < *b_bound)
          break;
        tmpc = b_bound - B.begin();
        if(memoc[tmpc] == -1){ // log2(N): Cのメモカ
          memoc[tmpc] = C.end() - upper_bound(C.begin(), C.end(), *b_bound); // log2(N)
        }
        memo[tmp] += memoc[tmpc];
      }
    }
    count += memo[tmp];
    prev_b_count = memo[tmp];
  }
  */

  // これ、もしかしてBを基準にしたほうが良いんか??
  // えー、コッチのほうが良いのか...
  // 確かに 2Nlog2(N)でいけるもんなぁ...
  for(auto b: B){   // N
    long a_count = lower_bound(A.begin(), A.end(), b) - A.begin(); // log2(N)
    long c_count = C.end() - upper_bound(C.begin(), C.end(), b);
    count += a_count * c_count;
  }

  cout << count << endl;
}