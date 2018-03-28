#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Solution{
public:
  int searchInsert(vector<int>& nums, int target){
    if(!nums.size()) return 0;
    int i=0;
    for(;i<nums.size();i++){
      if(nums[i]<target) continue;
      else break;
    }
    return i;
    //else return i;
  }
};

int main(){
  Solution search;
  vector<int> a;
  a.push_back(1);
  a.push_back(3);
  a.push_back(5);
  int target = 0;
  cout<<search.searchInsert(a, target);
  return 0;
}
