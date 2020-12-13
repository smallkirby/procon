#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

#define PI 3.14159265359

using namespace std;

int main(void)
{
  long N,M,T;
  bool result = true;
  long cur=0, cm=0;
  long ai,bi;
  cin >> N>>M>>T;
  cm = N;
  vector<long> a(M);
  vector<long> b(M);
  for(int ix=0;ix!=M;++ix)
    cin >> a.at(ix) >> b.at(ix);

  for(int ix=0;ix!=M;++ix){
    ai = a.at(ix);
    bi = b.at(ix);
    cm -= ai - cur;
    //cout << "IN: " << cm << endl;
    if(cm <= 0)
      break;
    //cout << bi-ai<<endl;
    cm += bi - ai;
    if(cm > N)
      cm = N;
    cur = bi;
    //cout << "OUT: " << cm << endl;
  }
  cm -= T - cur;
  if(cm <= 0)
    result = false;
  //cout << "IN: " << cm << endl;
  if(result)
    cout << "Yes"<<endl;
  else
    cout << "No"<<endl;
}