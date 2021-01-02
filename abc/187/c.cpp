#include<bits/stdc++.h>

using namespace std;

/******** end of Utility ***************/

int main(void)
{
  // input
  long N;
  cin >> N;
  auto a = vector<map<string,int>>(10); // !あり/長さごと 0は使わない
  auto b = vector<map<string,int>>(10); // !なし/長さごと 0は使わない
  vector<string> S = vector<string>(N);
  for(auto&& s: S){
    cin >> s;
    if(s[0] == '!'){
      ++a[s.length()-1][s.substr(1)];
    }else{
      if(s.length()==10)
        continue;
      ++b[s.length()][s];
    }
  }

  // main
  long l = 0;
  for(auto _b: b){    // 各文字列長さの!なし: map<string,int>
    for(auto c: _b){  // ある文字列
      if(a[c.first.length()][c.first] != 0){
        cout << c.first << endl;
        return 0;
      }
    }
  }
  cout << "satisfiable" << endl;

  // print
}