#include<iostream>
#include<vector>

using namespace std;

//

class Solution{
public:
  vector<vector<int>> permute(vector<int>& nums){
    vector<vector<int>> res;
    if(!nums.size())return res;
    for(int i=0;i<nums.size();i++){
      vector<int> temp;
      temp.push_back(nums[i]);
      for(int j=i+1;j<nums.size();j++){
        if()
      }
    }
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
