#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<vector>

using namespace std;


class Solution{
public:
  int majorityElement(vector<int>& nums){
    unordered_map<int, int> num;
    int n = nums.size();
    for(int i=0;i<n;i++){
      if(++num[nums[i]]>n/2) return nums[i];
    }
  }
};

int main(){
  vector<int> a={1,2,3,5,5,5,5,5};
  Solution mE;
  cout<<mE.majorityElement(a);
  return 0;
}
