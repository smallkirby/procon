#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

#define PI 3.14159265359

using namespace std;

int main(void)
{
  int n;
  string a;
  int m;
  cin >> n;
  vector<bool> s(13,false),h(13, false),c(13, false),d(13, false);

  for(int ix=0; ix!=n; ++ix){
    cin >> a >> m;
    --m;
    if(a == "S")
      s.at(m) = true;
    else if(a == "H")
      h.at(m) = true;
    else if(a == "C")
      c.at(m) = true;
    else if(a == "D")
      d.at(m) = true;
  }
  for(int ix=0;ix!=13;++ix)
    if(!s.at(ix))
      cout << "S " << ix+1 << endl;
  for(int ix=0;ix!=13;++ix)
    if(!h.at(ix))
      cout << "H " << ix+1 << endl;
  for(int ix=0;ix!=13;++ix)
    if(!c.at(ix))
      cout << "C " << ix+1 << endl;
  for(int ix=0;ix!=13;++ix)
    if(!d.at(ix))
      cout << "D " << ix+1 << endl;
}