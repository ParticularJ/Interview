#include<iostream>
#include<vector>

using namespace std;

//思路：要有log(n),思路是二分
//-∞             3 4 3           -∞
//-∞    res      5 4 3           -∞
//-∞             3 4 5     res      -∞
//-∞    res      3 2 6           -∞



class Solution{
public:
  long long cal(vector<int>& nums, int id){
    if(id==-1)return -(1<<40);
    else if(id==nums.size())return -(1<<40);
    else return nums[id];
  }
public:
  int findPeakElement(vector<int>& nums){
    if(nums.size()==0)return 0;
    int l=0,r=nums.size()-1;
    for(;l<=r;){
      long long mid = (l+r)>>1;
      long long lval = cal(nums, mid-1);
      long long rval = cal(nums, mid+1);
      long long mval = cal(nums, mid);
      if(mval>lval&&mval>rval)return mid;
      else if(mval>lval&&mval<rval)l=mid+1;
      else r=mid-1;
    }
  }
};

int main(){
  vector<int> a = {1, 2, 3, 1};
  Solution fPE;
  cout<<fPE.findPeakElement(a);
  return 0;
}
