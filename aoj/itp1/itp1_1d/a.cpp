#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void)
{
  int S, h, m, s;
  cin >> S;
  h = S / (60*60);
  S -= h*60*60;
  m = S / 60;
  S -= m*60;
  s = S;
  cout << h << ":" << m << ":" << s << endl;
}