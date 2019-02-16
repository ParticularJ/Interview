#include<iostream>

using namespace std;

// 思想：转化为二进制，统计1的个数
// s1： 循环以题目给的最高为循环
// s2: 异或后操作

class Solution{
public:
  int hammingDistance1(int x, int y){
    int res=0;
    for(int i=0;i<31;i++){
      int bx = x % 2;
      int by = y % 2;
      if(bx!=by)res++;


      x /=2;
      y /=2;
    }
    return res;
  }
  int hammingDistance2(int x, int y){
    int res=0;
    for(int i=0;i<31;i++){
      int bx = x % 2;
      int by = y % 2;
      if(bx!=by)res++;
      x /=2;
      y /=2;
    }
    return res;
  }
};


int main(){
  Solution hD;
  int x=1, y=4;
  cout<<hD.hammingDistance1(x, y)<<endl;
  cout<<hD.hammingDistance2(2, y)<<endl;
}
