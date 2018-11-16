#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//思路：
//使用DFS，将所有未被包围住的O的位置记录下来
//最后去更新所有这些位置的值
//行和列的关系一定要搞清楚

class Solution{
public:
  void solve(vector<vector<char> >& board){
    int row = board.size();
    int col = board[0].size();
    if(row==0||col==0)return;
    //记录边界上为O的位置
    vector<vector<int> > alive(row, vector<int>(col, 0));
    queue<pair<int, int>> que;
    // 对第一行和最后一行的记录
    for(int i=0;i<col;i++){
      if(board[0][i]=='O'){
        que.push(make_pair(0, i));
        alive[0][i]=1;
      }
      if(board[col-1][i]=='O'&&alive[col-1][i]==0){
        que.push(make_pair(col-1, i));
        alive[col-1][i]=1;
      }
    }
    //判断第一列于最后一列
    for(int i=0;i<row;i++){
      if(board[i][0]=='O'&&alive[i][0]==0){
        que.push(make_pair(i, 0));
        alive[i][0]=1;
      }
      if(board[i][row-1]=='O'&&alive[i][row-1]==0){
        que.push(make_pair(i, row-1));
        alive[i][row-1]=1;
      }
    }
    //判断与上述相邻的
    while(que.size()>0){
      pair<int, int> coor = que.front();
      que.pop();
      // 分别去判断里面一圈的值
      int dx[] = {0, -1, 0, 1};
      int dy[] = {1, 0, -1, 0};
      for(int index=0;index<3;index++){
        int x = coor.first+dx[index];
        int y = coor.second+dy[index];
        if(x>=0&&y>=0&&x<row&&y<col&&alive[x][y]==0&&board[x][y]=='O'){
          alive[x][y]=1;
          que.push(make_pair(x, y));
        }
      }
    }
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(alive[i][j]==0&&board[i][j]!='X')
          board[i][j]=='X';
      }
    }
  }
};


/*
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:

X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
Explanation:

Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.
*/
class Solution {
public:
	void solve(vector<vector<char> >& board) {
		int row = board.size();
		if (row == 0)
			return;
		int col = board[0].size();
		if (col == 0)
			return;

		for(int i=0;i<row;i++)
			for(int j=0;j<col;j++)

	}
};