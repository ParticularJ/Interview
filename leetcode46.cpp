#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//使用回溯法

class Solution{
public:
    vector<vector<int>> permute(vector<int>& nums){
    vector<vector<int>> res;
    int size=nums.size();
    sort(nums.begin(),nums.end());
    while(1){
      res.push_back(nums);
      if(size==0)return res;
      int assend = size-1;
      while(assend!=0 && nums[assend-1]>nums[assend])
        assend -= 1;
      if(assend==0)break;
      int mini = nums[assend-1];
      for(int i=size-1;i>=assend;i--){
        if(nums[i]>mini){
          swap(nums[i], nums[assend-1]);
          break;
        }
      }
      for(int i=assend, j=size-1;i <= j; i++,j--){
        swap(nums[i], nums[j]);
      }
    }
    return res;
  }
};

int main(){
  Solution p;
  vector<int> a = {1, 2, 3};
  vector<vector<int>> b;
  b = p.permute(a);
  for(auto c:b){
    for(auto d:c){
      cout<<d;
    }
  }
}
