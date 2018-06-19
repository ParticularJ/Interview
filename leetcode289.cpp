#include<iotream>
#include<vector>

using namespace std;

//解题思路：
// 我们需要通过一个简单的循环分别判断
// 当前位置的周围位置的信息，统计他们活着的出现次数
// 之后使用一个二进制的数去保存这一信息
// 活着的可能为10，11
// 其余元素则是0，1
// 统一右移一位，则就是更新后的信息

class Solution{
public:
  void gameOfLife(vector<vector<int> >& board){
    int m = board.size();
    int n = board[0].size();
    if(m==0||n==0)return;
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
        //记录1出现的次数
        int temp=0;
        // 八个方向
        for(int dx=-1;dx<2;dx++){
          for(int dy=-1;dy<2;dy++){
            if(i-dx>=0&&i-dx<m&&j-dy>=0&&j-dy<n&&!(dx==0&&dy==0)){
              temp += (board[i-dx][j-dy] & 1);
            }

          }
        }
        if((temp==2||temp==3)&&board[i][j]==1){
          board[i][j] |= 2;
        }
        else if(temp==3&&board[i][j]==0){
          board[i][j] |= 2;
        }
      }
    }
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
         board[i][j]>>=1;
      }
    }
  }
};
