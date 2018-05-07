#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//思路 ： 使用二分查找，寻找所需要的数，
// O(nlog(n))


class Solution{
public:
  int kthSmallest(vector<vector<int>>& matrix, int k){
    int mini = INT_MAX;
    int maxi = INT_MIN;
    for(auto &a:matrix){
      for(auto b:a){
        mini=min(b, min);
        maxi=max(b, max);
      }
    }
    int size = matrix.size();
    vector<int> L(size, 0);
    vector<int> R(matrix[0].size()-1,0);
    vector<int> cnt(size, 0);
    vector<int> res(size, 0);
    for(;mini<=maxi;){
      int mid = (maxi+mini)>>1;
      int sum=0;
      for(int i=0;i<size;i++){
        int l=L[i],r=R[i];
        int mid1 = (l+r)>>1;
        for(;l<=r;){
          if(matrix[i][mid1]>mid)
            res[i]=mid1,r=mid-1;
          else
            l=mid+1;
        }
        sum+=cnt[i]+(res[i]-l+1);
      }
      if(sum<k){
        for(int i=0;i<size;i++){
          cnt[i] += res[i]-L[i]+1;
          L[i] = result[i] + 1;
        }
        minii = mid +1;
      }else{
        for(int i=0;i<size;i++){
          R[i] = res[i];
        }
        maxi=mid-1;
        ret = mid;
      }
    }
    return ret;
  }
};


int main(){
  vector<vector<int>> a = {[1, 2, 3], [4, 5, 6], [7, 8, 9]};
  int b = 6;
  Solution a;
  cout<<a.kthSmallest(a, b);
}
