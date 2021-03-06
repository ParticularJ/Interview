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
private:
	int row, col;
	vector<vector<bool> > visited;
	int d[4][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };
	bool inArea(int x, int y) {
		return x >= 0 && x<row && y >= 0 && y<col;
	}

private:
	bool bfs(vector<vector<char> >& board, int x, int y, vector<pair<int, int> >& record) {
		queue<pair<int, int>> q;
		q.push(make_pair(x, y));
		visited[x][y] = true;
		bool ret = true;


		while (!q.empty()) {
			pair<int, int> start = q.front();
			q.pop();
			record.push_back(make_pair(start.first, start.second));
			for (int i = 0; i<4; i++) {
				int newX = start.first + d[i][0];
				int newY = start.second + d[i][1];
				if (!inArea(newX, newY))
					ret = false;
				else if (!visited[newX][newY] && board[newX][newY] == 'O') {
					visited[newX][newY] = true;
					q.push(make_pair(newX, newY));
				}
			}
		}
		return ret;
	}

public:
	void solve(vector<vector<char>>& board) {
		row = board.size();
		if (row == 0)
			return;
		col = board[0].size();
		if (col == 0)
			return;
		// 判断有没有走过某些位置
		visited = vector<vector<bool> >(row, vector<bool>(col, false));
		// 记录符合要求的'O'坐标
		vector<pair<int, int> > record;
		record.clear();
		for (int i = 0; i<row; i++) {
			for (int j = 0; j<col; j++) {
				if (!visited[i][j] && board[i][j] == 'O') {
					// 统计完一部分后要将之清零
					record.clear();
					if (bfs(board, i, j, record)) {
						for (int k = 0; k<record.size(); k++) {
							board[record[k].first][record[k].second] = 'X';
						}
					}
				}
			}
		}
		return;
	}
};