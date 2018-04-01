#include<iostream>
#include<vector>

using namespace std;

class Solution{
public:
    int removeDuplicated(vector<int>& nums, int& val){
        int a=0,size=nums.size();
        if(!size) return 0;
        for(int i=0;i!=size;++i){
            if(nums[i]!=val) {
                nums[++a] = nums[i];
            }
        }
        cout<<a;
        return a;
    }
};



int main(){
  Solution removeDup;
  vector<int> a;
  a.push_back(3);
  a.push_back(2);
  a.push_back(2);
  a.push_back(3);
  int b=3;
//  cout<<a.size();
  cout<<removeDup.removeDuplicated(a, b);
}
