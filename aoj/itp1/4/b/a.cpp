#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

#define PI 3.14159265359

using namespace std;

int main(void)
{
  int a,b;
  int res;
  string c;
  while(1==1){
    cin >> a >> c >> b;
    if(c=="+")
      res = a + b;
    else if(c=="-")
      res = a- b;
    else if(c=="/")
      res = a/b;
    else if(c=="*")
      res = a*b;
    else if(c=="?")
      break;
    cout << res << endl;
  }
}