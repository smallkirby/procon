#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

using namespace std;

int main(void)
{
  long a,b;
  cin >>a>>b;
  cout <<a/b<<" "<<a%b<<" "<< fixed << setprecision(5)  << (double)a/(double)b<<endl;
}