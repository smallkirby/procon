#include<bits/stdc++.h>

#define PI 3.14159265359

using namespace std;

#define rep_(i, a_, b_, a, b, ...) for (int i = (a), i##_len = (b); i < i##_len; ++i)
#define rep(i, ...) rep_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)

using llong = long long;

/******** Utility ***************/

// Calculate (a ^ b) % mod
// O(log`mod`)
llong modpow(llong a, llong b, llong mod) {
  llong p = 1, q = a;
  for (int ix = 0; ix != 30; ++ix) {
    if ((b & (1LL << ix)) != 0) {
      p *= q;
      p %= mod;
    }
    q *= q;
    q %= mod;
  }

  return p;
}

// Calculate inv of a/b under mod, based on Fermat's little theorem
// O(log`mod`)
llong moddiv(llong a, llong b, llong mod) {
  return (a * modpow(b, mod - 2, mod)) % mod;
}

vector<llong> _factorial_memo, _factorial_inv_memo;
void init_factorial_memo(size_t N, llong mod) {
  if (_factorial_memo.empty()) {
    _factorial_memo.resize(N+1, 0);
    _factorial_inv_memo.resize(N+1, 0);
    _factorial_memo[0] = 1;
    for (size_t ix = 1; ix <= N; ++ix)
      _factorial_memo[ix] = (1LL * ix * _factorial_memo[ix - 1]) % mod;
    for (size_t ix = 0; ix <= N; ++ix)
      _factorial_inv_memo[ix] = moddiv(1LL, _factorial_memo[ix], mod);
  }
}

// O(log`mod`)
llong nCr(int n, int r, llong mod) {
  if (n < r || r < 0) return 0;
  if (_factorial_memo.empty()) init_factorial_memo(n, mod);
  return (_factorial_memo[n] * _factorial_inv_memo[r] % mod) * _factorial_inv_memo[n - r] % mod;
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

/******** end of Utility ***************/

int main(void)
{
  // input
  ulong N,A,B; cin >> N >> A >> B;

  // main
  for (int h = 0; h != N; ++h) {
    for (int sh = 0; sh != A; ++sh) {
      for (int w = 0; w != N; ++w) {
        if ((h + w)%2 == 0) {
          cout << string(B, '.');
        } else {
          cout << string(B, '#');
        }
      }
      cout << endl;
    }
  }

  // print
}
