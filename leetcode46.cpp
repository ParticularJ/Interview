#include<iostream>
#include<vector>

using namespace std;

//使用回溯法

class Solution{
public:
  void helper(vector<vector<int>>& res, vector<int>& temp, vector<int>& nums){
    if(temp.size()==nums.size()){
      res.push_back(temp);
      return;
    }
    for(int i=0;i<nums.size();i++){
      if(temp[nums[i]])continue;
      temp.push_back(nums[i]);
      helper(res, temp, nums);
      temp.erase(temp.end()-1);
    }
  }
public:
  vector<vector<int>> permute(vector<int>& nums){
    vector<vector<int>> res;
    if(!nums.size())return res;
    vector<int> temp;
    helper(res, temp, nums);
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
