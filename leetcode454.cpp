#include<iostream>
#include<vector>
#include<unordered_map>
//思路：因为a+b+c+d = 0;
// 可以转化为 a+b=-c-d ;
// 使用hash_map
using namespace std;

class Solution{
public:
  int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D){
    unordered_map<int, int> mymap;
    int res=0;
    for(auto a:A){
      for(auto b:B){
        int sum=a+b;
        mymap[sum] += 1;
      }
    }

    for(auto c:C){
      for(auto d:D){
        int sum1 = -c-d;
        res += mymap[sum1];
      }
    }
    return res;
   }
};


int main(){
  Solution sum;
  vector<int> A = {1, 1};
  vector<int> B = {2, -1};
  vector<int> C = {-1, 2};
  vector<int> D = {-1, -2};
  cout<<sum.fourSumCount(A, B, C, D);
  return 0;

}
