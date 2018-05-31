#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Solution{
public:
  static string convert(int a){
    char temp[20];
    sprintf(temp, "%d", a);
    return string(temp);
  }
  static bool cmp(int &a, int &b){
    string s = convert(a), l = convert(b);
    cout<<s+l<<" "<<l+s<<endl;
    return s+l>l+s;
  }
  string largesetNumber(vector<int>& nums){
    sort(nums.begin(), nums.end(),cmp);
    string res="";
    for(auto s:nums){
      res+=convert(s);
    }
    return res;
  }
};


int main(){
  vector<int> a = {10, 2};
  Solution lN;
  string res;
  res = lN.largesetNumber(a);
  cout<<res;
  return 0;
}
