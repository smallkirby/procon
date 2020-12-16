#include <iostream>
#include <vector>
#include <string>
#include<iomanip>
#include <cmath>
#include<algorithm>
#include<numeric>
#include<cassert>

#define PI 3.14159265359

using namespace std;

/******** Utility ***************/
#define max(a,b) (a<b ? b : a)
#define min(a,b) (a>b ? b : a)

int bsize(int bits, int _max){
  int c = 0;
  for(int ix=0; ix!=_max; ++ix)
    if((bits&(1<<ix)) !=0){
      ++c;
    }
  return c;
}

long factrial(long n){
  assert(n >= 0);
  if(n <= 1)
    return 1;
  long _sum = 1;
  for(int ix=0; ix!=(n-1); ++ix)
    _sum *= n-ix;
  return _sum;
}

void show(vector<int> v)
{
  for(auto _v: v)
    cout << _v << " ";
  cout << endl;
}

void show2(vector<vector<int>> v)
{
  for(auto __v: v){
    cout << "(";
    for(auto _v: __v){
      cout << _v << ", ";
    }
    cout << ")" << endl;
  }
}
/******** end of Utility ***************/

int k;
// ボードの状態: 0: 何もない 1以上: queenもしくはその延長線上
vector<vector<int>> board(8, vector<int>(8,0)); // ボードのqueen・延長線マーカ
vector<vector<int>> kakutei; // 確定したボードの情報: (col, row)
vector<int> kakutei_row;

void showEncho(vector<vector<int>> v)
{
  cout << "+++++++++++++++" << endl;
  for(auto row: v){
    for(auto c: row){
      cout << c << " ";
    }
    cout << endl;
  }
}

void subSetQueen(int _row, int _col, int val, vector<vector<int>> &v)
{
  int trow, tcol, sa;
  v[_row][_col] -= val*3;

  for(int ix=0; ix!=8; ++ix){ // 縦横
    v[_row][ix] += val;
    v[ix][_col] += val;
  }

  trow = _row;
  tcol = _col;
  sa = tcol - trow;
  for(int row=0; row!=8; ++row){ // 左上-右下斜め
    if(row + sa >= 8)
      break;
    if(row + sa < 0)
      continue;
    v[row][row+sa] += val;
  }

  sa = _col + _row;
  for(int row=0; row!=8; ++row){ // 左上-右下斜め
    if(sa-row >= 8){
      continue;
    }
    if(sa-row < 0)
      break;
    v[row][sa-row] += val;
  }
}

// queenをセットして、延長線上ライン等を決める
void setQueen(int row, int col, vector<vector<int>> &v)
{
  subSetQueen(row, col, 1, v);
  kakutei.push_back({col,row});
  kakutei_row.push_back(row);
}

void unsetQueen(int row, int col, vector<vector<int>> &v)
{
  subSetQueen(row, col, -1, v);
  kakutei.pop_back();
  kakutei_row.pop_back();
}

void showBoard()
{
  for(int row=0; row!=8; ++row){
    int hoge = -1;
    for(auto k: kakutei){
      if(k[1] == row){
        hoge = k[0];
        break;
      }
    }
    for(int col=0; col!=8; ++col){
      if(col == hoge)
        cout << "Q";
      else
        cout << ".";
    }
    cout << endl;
  }
}

// i行目のqueenの場所を決める
bool func(int row)
{
  int col = 0;
  if(row>=8){
    return true;
  }

  if(count(kakutei_row.begin(), kakutei_row.end(), row) == 1)
    return func(row+1);
  else{
    while(true){
      if(col == 8)
        break;

      if(board[row][col] > 0){
        ++col;
        continue;
      }
      setQueen(row, col, board);
      if(func(row+1)){
        return true;
      }
      unsetQueen(row, col, board);

      ++col;
    }
    return false;
  }
}

int main(void)
{
  // input
  int row,col;
  cin >> k;
  for(int ix=0; ix!=k; ++ix){
    cin >> row >> col;
    setQueen(row, col, board);
  }

  // main
  /*
  うーん。
  何も工夫しないとすると、とりあえず各行に1つずつしか置けないから、その条件のもとで全探索かなぁ...
  */
  assert(func(0) == true);
  showBoard();
  return 0;
}