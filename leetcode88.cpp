#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution{
public:
  vector<int> merge(vector<int>& nums1, int m, vector<int>& nums2, int n){
    //int a = m>n? n:m;
    int a = m-1;
    int b = n-1;
    int temp = m+n-1;
    while(a>=0 && b>=0){
      nums1[temp--] = nums1[a] >= nums2[b] ? nums1[a--]:nums2[b--];
    }
    while(b>=0){
      nums1[temp--] = nums2[b--];
    }
    return nums1;
  }

};


int main(){
  vector<int> a = {1,2,3,4, 0, 0,0};
  vector<int> b = {2, 3, 4};
  Solution mer;
  vector<int> c;
  c=mer.merge(a,4,b,3);
  for(auto s:c){
    cout<<s;
  }
}
