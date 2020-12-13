#include <iostream>
#include <vector>
#include <string>
#include<iomanip>
#include<unistd.h>

#define PI 3.14159265359

using namespace std;

bool check_sort(vector<int> ns){
  for(int ix=0;ix!=ns.size()-1;++ix)
    if(ns.at(ix) > ns.at(ix+1))
      return false;
  return true;
}

int sumvec(vector<int> ns){
  int sum = 0;
  for(auto n: ns)
    sum += n;
  return sum;
}
int sumx(vector<int> ns, int m){
  int sum = 0;
  for(int ix=0; ix!=m; ++ix)
    sum += ns.at(ix);
  return sum;
}
int min(int a, int b){
  return a < b ? a : b;
}
void show(vector<int> ns){
  for(auto n: ns)
    cout << n << " ";
  cout << endl;
}

vector<int> maxvec(vector<int> ns, int max, int sum){
  int _sum = 0;
  for(int ix=0;ix!=ns.size();++ix)
    ns.at(ix) = 1;
  _sum = sumvec(ns);
  if(_sum == sum)
    return ns;
  ns.at(ns.size()-1) = sum-_sum > max ? sum-_sum : max;
}

int main(void)
{
  int L;
  cin >> L;
  vector<int> ns(12);
  vector<int> nmax(12);
  long count = 0;
  int max,sum,unfix,rest;
  int trush;

  while(1==1){
    // init
    cout << "wai"<<endl;
    unfix = 11;
    max = L-12;
    rest = L-12;

    //
    while(1==1){
      int p = min(rest, max);
      if(p <= 0)
        break;
      ns.at(unfix) += p;
      rest -= p;
      if(rest <= 0)
        break;
      max = p;
      --unfix;
    }
    show(ns);
    --max;
  }

}