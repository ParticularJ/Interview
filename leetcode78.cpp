#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//思路：根据位运算，总共生成的字串个数为2^nums.size()次方
// 通过位运算判断nums的下表是否添加到了结果中
// 重点是位运算，& 

class Solution{
public:
  vector<vector<int>> subset(vector<int>& nums){
    int size = nums.size();
    int maxi = 1<<size;
    vector<vector<int>> res;
    for(int i=0;i<maxi;i++){
      vector<int> temp;
      for(int j=0;j<size;j++){
        if((1<<j)&i)==1)
        temp.push_back(nums[i]);
      }
      res.push_back(temp);
    }
    return res;
  }
};


int main(){
  Solution sub;
  vector<int> a = {1, 2, 3};
  vector<vector<int>> b;
  b = sub.subset(a);
  for(auto c:b){
    for(auto d:c){
      cout<<d<<" ";
    }
  }
  return 0;
}


/*
Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: nums = [1,2,3]
Output:
[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]
*/
class Solution {
public:
	vector<vector<int> > res;
	void dfs(int index, vector<int>& nums, vector<int>& temp) {
		res.push_back(temp);
		for (int i = index; i < nums.size(); i++) {
			temp.push_back(nums[i]);
			dfs(i+1, nums, temp);
			temp.pop_back();
		}
	}
	vector<vector<int>> subsets(vector<int>& nums) {
		res.clear();
		int size = nums.size();
		if (size == 0)
			return res;
		vector<int> temp;
		dfs(nums, temp);
		return res;
	}
};

