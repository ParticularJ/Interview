#include<iostream>
#include<vector>

// 思路：我们分别对元素进行左侧乘，右侧乘
// 最后返回我们的结果
// 1 2 3 4
//左乘 1，   1， 2， 6
//右乘 24， 12， 4， 1
//结合 24， 12， 8， 6

using namespace std;

class Solution{
public:
  vector<int> productExceptSelf(vector<int>& nums){
    //if(!nums.size()||nums.size()==1)return 0;
    int temp=1;
    vector<int> res(nums.size(),1);
    for(int i=0;i<nums.size();i++){
      res[i] *= temp;
      temp *= nums[i];
    }
    temp=1;
    for(int i=nums.size()-1;i>=0;i--){
      res[i] *= temp;
    //  cout<<res[i];
      temp *= nums[i];
    }
    return res;
  }
};


int main(){
  Solution pE;
  vector<int> a = {1, 2, 3, 4};
  vector<int> b;
  b=pE.productExceptSelf(a);
  for(auto c:b){
    cout<<c<<" ";
  }
}
