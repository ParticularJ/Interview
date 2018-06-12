#include<iostream>
#include<vector>
#include<queue>

// 我们需要维护一个数组，用来记录每一次平方之后的值
// 其次，我们需要一个队列，因为队列可以先进先出，这样每次
// 取队列的首元素，我们可以对比下一次的平方数
// 主要使用广度优先遍历

using namespace std;

class Solution{
public:
  int numSquares(int n){
    vector<int> square(n+1, -1);
    square[0]=0;
    queue<int> que;
    que.push(0);
    for(;que.empty()==false;que.pop()){
      int m = que.front();
      for(int i=1;i*i+m<=n;i++){
        if(square[i*i+m]==-1){
          square[i*i+m]=square[m]+1;
          que.push(i*i+m);
        }
      }
    }
    return square[n];
  }
};

int main(){
  Solution nS;
  int a = 12;
  cout<<nS.numSquares(a)<<endl;
  return 0;
}
