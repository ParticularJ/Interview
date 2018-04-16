#include<iostream>
#include<vector>
#include<string>

//思路就是分别去求解不同子字符串的和
// 用到动态规划(dp),我在之前每一步选取最大，肯定得到的最大
// 一定记得对所有的定义进行初始化，否则就会报错
using namespace std;

class Solution{
public:
  int maxSubArray(vector<int>& nums){
    vector<int> dp(nums.size());
    dp[0]=nums[0];
    int max1=dp[0];
    for(int i=1;i<nums.size();i++){
      dp[i]= ((dp[i-1]+nums[i])>nums[i]) ? (dp[i-1]+nums[i]):nums[i];
      max1 = max1>dp[i]?max1:dp[i];
    }
    return max1;
  }
};

int main(){
  Solution maxsubarray;
  vector<int> a = {-2,1,-3,4,-1,2,1,-5,4};
  cout<<a[4];
  cout<<maxsubarray.maxSubArray(a);

}
