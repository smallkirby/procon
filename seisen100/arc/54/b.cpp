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


/******** end of Utility ***************/

double P;

double func(double x)
{
  return x +  P * pow(2.0, -1.0*x/1.5);
}

int main(void)
{
  cin >> P;

  double left = 0.0;
  double right = P;
  double lmed, rmed;
  double delta = pow(10.0, -10.0);
  //cout << std::fixed << std::setprecision(10)  << delta << endl;
  while(right - left > delta){
    //cout << std::fixed << std::setprecision(10)  << left << " : " << right << endl;
    lmed = left + (right-left)/3.0 * 1.0;
    rmed = left + (right-left)/3.0 * 2.0;
    if(func(lmed) < func(rmed)){
      right = rmed;
    }else{
      left = lmed;
    }
  }

  cout << std::fixed << std::setprecision(10) << func((left+right)/2.0) << endl;
}