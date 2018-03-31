#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>

//使用c++的sort算法，排序后前后比较，即可得到。
using namespace std;

class Solution{
public:
  int singleNumber(vector<int>& nums){
    if(!nums.size()) return 0;
    sort(nums.begin(), nums.end());
    for(int i=0;i<nums.size();i+=2){
      if(nums[i]!=nums[i+1]) return nums[i];
    }
  }
public:
  int singleNumber1(vector<int>& nums){
    int sum=0;
    for(int i=0;i<nums.size();i++){
      sum ^= nums[i];
      cout<<sum<<endl;
    }
    return sum;
  }
};

void main(){
  Solution sN;
  vector<int> a = {1,2,3,3,2,1,5};
  //cout<<sN.singleNumber(a);
  cout<<sN.singleNumber1(a);
}
