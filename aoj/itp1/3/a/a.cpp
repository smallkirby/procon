#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void)
{
  int x;
  for(int ix=0; 1==1; ++ix){
    cin >> x;
    if(x==0)
      break;
    //cout << format("Case %d: %d", ix+1, x) << endl;;
    cout << "Case "<<ix+1<<": "<<x << endl;
  }
}