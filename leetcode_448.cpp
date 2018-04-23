#include<iostream>
#include<vector>
#include<math.h>

using namespace std;
//主要思想：见到1-n，把对应位置的数字取负，输出非负数字
class Solution{
public:
  vector<int> findDisappearedNumbers(vector<int>& nums){
    vector<int> res;
    int len = nums.size();
    for(int i=0;i<len;i++){
      int index = abs(nums[i])-1;
      if(nums[index]>0){
        nums[index]=-nums[index];
      }
    }
    for(int i=0;i<len;i++){
      if(nums[i] > 0)res.push_back(i+1);
    }
  return res;
}
};

int main(){
  Solution fDN;
  vector<int> a ={4,3,2,7,8,2,3,1};
  vector<int> res;
  res = fDN.findDisappearedNumbers(a);
  for(auto s:res){
    cout<<s;
  }
}
