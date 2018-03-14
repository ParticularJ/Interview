#include<iostream>
#include<vector>

using namespace std;

class Solution{
public:
    int removeDuplicated(vector<int>& nums){
        int a=0,size=nums.size();
        if(!size) return 0;
        for(int i=0;i!=size;++i){
            if(nums[i]!=nums[a]) {
                nums[++a] = nums[i];
            }
        }
        return a+1;
    }
};



int main(){
  Solution removeDup;
  vector<int> a;
  a.push_back(1);
  a.push_back(2);
  a.push_back(2);
  a.push_back(3);
  cout<<a.size();
  cout<<removeDup.removeDuplicated(a);
}
