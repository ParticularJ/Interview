#include<iostream>
#include<vector>

using namespace std;

// 动态规划

class Solution{
public:
  int uniquePaths3(int m, int n){
    if(m==1||n==1)return 1;
    m-=1;
    n-=1;
    double res =1 ;
    for(int i=1;i<n+1;i++){
      res *= (m+n-i+1) / i;
    }
    return (int)res;
  }
public:
  int uniquePaths1(int m, int n){
    if(m==1||n==1)return 1;
    vector<int> res(m, 0);
    res[0]=1;
    for(int i=0;i<m;i++){
      for(int j=1;j<n;j++){
          res[j]=res[j]+res[j-1];
      }
    }
    return res[n-1];
  }
public:
  int uniquePaths(int m, int n){
    if(m==1||n==1)return 1;
    //初始化二元数组
    vector<vector<int>> res(m, vector<int>(n, 0));
    for(int i=0;i<m;i++){
      res[i][0] = 1;
    }
    for(int j=0;j<n;j++){
      res[0][j] = 1;
    }
    for(int i=1;i<m;i++){
      for(int j=1;j<n;j++){
        res[i][j] = res[i-1][j] + res[i][j-1];
      }
    }
    return res[m-1][n-1];
  }
};

int main(){
  Solution uP;
  int m=3, n=2;
  cout<<uP.uniquePaths(m, n);
  cout<<uP.uniquePaths1(m, n);
  cout<<uP.uniquePaths3(m,n);
  return 0;
}


/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


Above is a 7 x 3 grid. How many possible unique paths are there?

Note: m and n will be at most 100.

Example 1:

Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right
Example 2:

Input: m = 7, n = 3
Output: 28

*/

class Solution {
public:
	int uniquePaths(int m, int n) {
		assert(m > 0 && n > 0);
		vector<vector<int> > memo(m + 1, vector<int>(n + 1, 0));
		for (int i = 0; i < m; i++)
			memo[i][0] = 1;
		for (int j = 0; j < n; j++)
			memo[0][j] = 1;
		for (int i = 1; i < m; i++)
			for (int j = 1; j < n; j++)
				memo[i][j] = memo[i - 1][j] + memo[i][j - 1];
		return memo[m][n];
	}

};