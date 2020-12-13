#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

#define PI 3.14159265359

using namespace std;

int main(void)
{
  int H,W;
  while(1==1){
    cin >> H >> W;
    if(H==0 && W==0)
      break;
    for(int h=0;h!=H;++h){
      for(int w=0;w!=W;++w){
        if((h%2==0 && w%2==0) || (h%2==1 && w%2==1))
          cout << "#";
        else
          cout << ".";
      }
      cout << endl;
    }
    cout << endl;
  }
}