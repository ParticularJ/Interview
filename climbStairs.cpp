#include<iostream>
#include<vector>
#include<string>
#include<iterator>

using namespace std;

//动态规划，只与前两个有关。
//递归，但是某些需要计算两次,会发生runtime error 


class Solution{
public:
  int climbStairs(int n){
    if(n==1) return 1;
    if(n==2) return 2;
    if(n>2) return climbStairs(n-1) + climbStairs(n-2);
  }
public:
  int climbStairs1(int n){
    int dp1=1, dp2=2, res=0;
    if(n<=2) return dp1;
    if(n==3) return dp2;
    //if(n==2) return dp2;
    while((n--)-2){
      res = dp1+dp2;
      dp1 = dp2;
      dp2 = res;
      //cout<<dp2<<' '<<dp1<<endl;
    }
    return res;
  }
};

void main(){
  Solution cs;
  int a = 6;
  cout<<cs.climbStairs(a)<<endl;
  cout<<cs.climbStairs1(a);
}
