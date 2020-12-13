#include <iostream>
#include <vector>
#include <string>
#include<iomanip>
#include <cmath>
#include<algorithm>
#include <functional>

#define PI 3.14159265359

using namespace std;

#define max(a,b) (a<b ? b : a)
#define min(a,b) (a>b ? b : a)
#define abs(n) ((n)>=0 ? (n) : -1*(n))

#define M 1000000000

int main(void)
{
  int N;
  cin >> N;

  vector<long> A(N);
  vector<long> B(N);
  //vector<long> best(3, pow(2,30)); // time, enter, exit
  long count=0;
  for(int ix=0;ix!=N;++ix){
    cin >> A[ix] >> B[ix];
  }

  /* これだと流石に終わらない */
  // 脳死で全探索を考えると、[各人の最小値,各人の最大値]でかつ入り口<出口になるように全探索するんかなぁ
  // 入り口と出口は逆でも同じだから、入り口<=出口とする
  // これ、A/Bってこの順に経由しなくちゃいけないんかな
  //long _min = min(*min_element(A.begin(), A.end()), *min_element(B.begin(), B.end()));
  //long _max = max(*max_element(A.begin(), A.end()), *max_element(B.begin(), B.end()));
  ////cout <<"cand " << _min << ":" << _max << endl;
  //for(int enter=_min; enter<=_max; ++enter){
  //  for(int exi=enter; exi<=_max; ++exi){
  //    count = 0;
  //    for(int ix=0; ix!=N; ++ix){
  //      count += abs(A[ix] - enter) + abs(B[ix] - A[ix]) + abs(B[ix] - exi);
  //      /*
  //      if(enter==5 && exi==10){
  //        cout << "\t" << A[ix]-enter << endl;
  //      }
  //      */
  //    }
  //    if(count < best[0]){
  //      best[0] = count;
  //      best[1] = enter;
  //      best[2] = exi;
  //      //cout << best[0] << "=" << best[1] << "=" << best[2] << endl;
  //    }
  //  }
  //}

  // AとBは逆でもいいらしい
  // 上の式の、この部分
  //      count += abs(A[ix] - enter) + abs(B[ix] - A[ix]) + abs(B[ix] - exi);
  // これは、あってる。これをすべてのixについて考えると以下の3つの和
  //    abs(A0 - enter) + abs(A1 - enter) + ... + abs(A[N-1] - enter)
  //    abs(B0 - exit) + abs(B1 - exit) + ... + abs(B[N-1] - exit)
  //    abs(A0 - B0) + abs(A1 - B1) + ... + abs(A[N-1] - B[N-1])
  // 3つめは固定
  // 1つ目を最小にするようなenterは、A[ix]の中央値になる!!
  // 2つ目も同様
  for(int ix=0; ix!=N; ++ix)
    count += abs(A[ix] - B[ix]);
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  long enter, exi;
  if(N%2!=0){
    enter = A[A.size()/2];
    exi = B[B.size()/2];
    for(int ix=0;ix!=N;++ix){
      count += abs(A[ix]-enter) + abs(B[ix]-exi);
      //cout << "\t" << abs(A[ix]-enter) << "K" << abs(B[ix]-enter)<<endl;
    }
  }else{
    long c1=0,c2=0,c3=0,c4=0;
    enter = A[A.size()/2];
    exi = B[B.size()/2];
    for(int ix=0;ix!=N;++ix)
      c1 += abs(A[ix]-enter) + abs(B[ix]-exi);
    enter = A[A.size()/2-1];
    exi = B[B.size()/2];
    for(int ix=0;ix!=N;++ix)
      c2 += abs(A[ix]-enter) + abs(B[ix]-exi);
    enter = A[A.size()/2-1];
    exi = B[B.size()/2-1];
    for(int ix=0;ix!=N;++ix)
      c3 += abs(A[ix]-enter) + abs(B[ix]-enter);
    enter = A[A.size()/2];
    exi = B[B.size()/2-1];
    for(int ix=0;ix!=N;++ix)
      c4 += abs(A[ix]-enter) + abs(B[ix]-enter);
    count += (std::min)({c1,c2,c3,c4});
  }

  cout << count << endl;
  //cout << best[1] << ":" << best[2] << endl;
}