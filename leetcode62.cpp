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
