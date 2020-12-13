#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void)
{
  int a,b;
  cin >> a >> b;
  if(a > b)
    cout << "a > b" << endl;
  else if(a == b)
    cout << "a == b" << endl;
  else if(a < b)
    cout << "a < b" << endl;
}