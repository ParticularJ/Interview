#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution{
public:
  vector<int> merge(vector<int>& nums1, int m, vector<int>& nums2, int n){
    //int a = m>n? n:m;
    for(int i=0;i<n;i++){
      nums1.push_back(nums2[i]);
    }
    sort(nums1.begin(), nums1.end());
    return nums1;
  }

};


int main(){
  vector<int> a = {1,2,3,4};
  vector<int> b = {2, 3, 4};
  Solution mer;
  vector<int> c;
  c=mer.merge(a,3,b,3);
  for(auto s:c){
    cout<<s;
  }
}
