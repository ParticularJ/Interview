#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//按顺序添加之后，交换位置，再次添加，直到结束。

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
      // 通过assend判断是否降序完成，
      while(assend!=0 && nums[assend-1]>nums[assend])
        assend -= 1;
      if(assend==0)break;
      // 与前一个比较，如果后一个大于前一个交换二者位置
      int mini = nums[assend-1];
      for(int i=size-1;i>=assend;i--){
        if(nums[i]>mini){
          swap(nums[i], nums[assend-1]);
          break;
        }
      }
      // 类似排序，如将上一步得到的2，3，1，变为2，1，3
      for(int i=assend, j=size-1;i <= j; i++,j--){
        swap(nums[i], nums[j]);
      }
    }
    return res;
  }
};

int main(){
  Solution p;
  vector<int> a = {1, 2, 3, 4};
  vector<vector<int>> b;
  b = p.permute(a);
  for(auto c:b){
    for(auto d:c){
      cout<<d;
    }
  }
}
