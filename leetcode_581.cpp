#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<math.h>

using namespace std;

// 掌握stack的使用,使用栈的方法，让它与栈顶元素比较，
// 给定两个边界。

class Solution{
public:
  int findUnsortedSubarray(vector<int>& nums){
    stack<int> st;
    int left = nums.size() + 1, right=-1;
    for(int i=0;i<nums.size();i++){
      int n = nums[i];
      while(!st.empty() && nums[st.top()] > n){
        left = min(left, st.top());
        st.pop();
      }
      st.push(i);
    }
    if(left== nums.size()+1 || nums.size()==0)return 0;
    for(;st.empty()==false;st.pop());
    for(int i=nums.size()-1;i>=0;i--){
      int n = nums[i];
      while(!st.empty() && nums[st.top()] < n){
        right = max(right, st.top());
        st.pop();
      }
      st.push(i);
    }
    return right-left+1;
  }
};


int main(){
  Solution s;
  vector<int> a = {1, 3, 2, 4};
  cout<<s.findUnsortedSubarray(a);
  return 0;
}
