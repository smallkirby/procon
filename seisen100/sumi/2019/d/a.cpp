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
  int N;
  long count = 0;
  string S;
  cin >> N >> S;
  vector<vector<vector<bool>>> vs(10, vector<vector<bool>>(10, vector<bool>(10, false)));
  vector<short> s(N);
  for(int ix=0;ix!=N;++ix){
    s[ix] = S[ix]-0x30;
  }

  for(int i1=0; i1!=N-2; ++i1){
    for(int i2=i1+1; i2!=N-1; ++i2){
      for(int i3=i2+1; i3!=N; ++i3){
        vs[s[i1]][s[i2]][s[i3]] = true;
        //cout << s[i1] << ":" << s[i2] << ":" << s[i3] << endl;
        //cout << vs[s[i1]][s[i2]][s[i3]] << endl;
      }
    }
  }

  for(int i1=0; i1!=10; ++i1){
    for(int i2=0; i2!=10; ++i2){
      for(int i3=0; i3!=10; ++i3){
        if(vs[i1][i2][i3])
          ++count;
      }
    }
  }
  //cout << endl << vs[0][2][2] << ", " << vs[0][2][4] << ", " << vs[2][2][4] << endl;
  cout << count << endl;
}