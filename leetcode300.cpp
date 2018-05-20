#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//思路：我们每次去存取一个最小值，这样返回最后的哪个坐标即可
// 10， 9， 2， 5， 3
// 我们只存2， 3，返回3的坐标+1即2


class Solution{
public:
  int lengthOfLIS(vector<int>& nums){
    int res=0;
    if(nums.size()==0)return res;
    vector<int> temp(nums.size()+1, (1<<31)-1);
    temp[0] = -(1<<31);
    cout<<temp[1];
    for(int i=0;i<nums.size();i++){
      int ans=0;
      for(int l=0,r=res;l<=r;){
        int mid = (l+r)>>1;
        if(nums[i]>temp[mid]){
          ans=mid;
          l=mid+1;
        }else{
          r=mid-1;
        }
      }
      temp[ans+1]=min(nums[i], temp[ans+1]);
      if(temp[ans+1]<((1<<31)-1)){
        res = max(ans+1,res);
      //  cout<<res;
      }
    }
    return res;
  }
};

int main(){
  Solution lOLIS;
  vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
  cout<<lOLIS.lengthOfLIS(a);
  return 0;
}
