#include <iostream>
#include <vector>
#include <string>
#include<iomanip>
#include <cmath>
#include<algorithm>

#define PI 3.14159265359

using namespace std;

#define max(a,b) (a<b ? b : a)
#define min(a,b) (a>b ? b : a)

int main(void)
{
  long A,B,C,X,Y, m=0;
  vector<long> temp;
  cin >>A>>B>>C>>X>>Y;

  if(A<C && B<C){
    cout << A*X + B*Y << endl;
    return 0;
  }else if(A<C && B>C){
    for(int c=0; c<=Y*2; c+=2){
      temp.push_back(A*(max(X-c/2, 0)) + B*(max(Y-c/2, 0)) + C*c);
    }
    cout << *min_element(temp.begin(), temp.end()) << endl;
    return 0;
  }else if(B<C && A>C){
    for(int c=0; c<=X*2; c+=2){
      temp.push_back(A*(max(X-c/2,0)) + B*(max(Y-c/2,0)) + C*c);
    }
    cout << *min_element(temp.begin(), temp.end()) << endl;
    return 0;
  }else{
    m = max(X,Y);
    for(int c=0; c<=m*2; c+=2){
      temp.push_back(A*(max(X-c/2,0)) + B*(max(Y-c/2,0)) + C*c);
    }
    cout << *min_element(temp.begin(), temp.end()) << endl;
    return 0;
  }
}