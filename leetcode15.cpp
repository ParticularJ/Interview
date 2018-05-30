#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//思路，


class Solution{
public:
  vector<vector<int>> threeSum(vector<int>& nums){
    int size = nums.size();
    sort(nums.begin(),nums.end());
    vector<vector<int> > res;
    for(int i=0;i<nums.size();i++){
      int sum = -nums[i];
      int front = i+1;
      int back = size-1;
      while(front<back){
        if(nums[front]+nums[back]<sum)front++;
        else if(nums[front]+nums[back]>sum)back--;
        else{
          vector<int> temp(3,0);
          temp[0]=nums[i];
          temp[1]=nums[front];
          temp[2]=nums[back];
          res.push_back(temp);
          while(front<back&&nums[front]==temp[1])front++;
          while(front<back&&nums[back]==temp[2])back--;
        }
      }
      while(i+1<nums.size() && nums[i+1]==nums[i])i++;
    }
    return res;
  }
};


int main(){
  vector<int> a =  {-1, 0, 1, 2, -1, -4};
  Solution tS;
  vector<vector<int> > b;
  b = tS.threeSum(a);
  for(auto c:b){
    for(auto e:c){
      cout<<e;
    }
  }
}
