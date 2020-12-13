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

  /*
  for(int i1=0; i1!=N-2; ++i1){
    for(int i2=i1+1; i2!=N-1; ++i2){
      for(int ix=0; ix!=10; ++ix)
        if(s.end() != find(s.begin()+i2+1, s.end(), ix))
          vs[s[i1]][s[i2]][ix] = true;
        //cout << s[i1] << ":" << s[i2] << ":" << s[i3] << endl;
        //cout << vs[s[i1]][s[i2]][s[i3]] << endl;
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
  */
 for(int i1=0; i1!=10; ++i1){
   auto iter1 = find(s.begin(), s.end(), i1);
   if(iter1==s.end() || iter1>=s.end()-2)
    continue;
   for(int i2=0; i2!=10; ++i2){
     auto iter2 = find(iter1+1, s.end(), i2);
     if(iter2==s.end() || iter2>=s.end()-1)
      continue;
     for(int i3=0; i3!=10; ++i3){
       auto iter3 = find(iter2+1, s.end(), i3);
       if(iter3 != s.end())
        ++count;
     }
   }
 }
  //cout << endl << vs[0][2][2] << ", " << vs[0][2][4] << ", " << vs[2][2][4] << endl;
  cout << count << endl;
}