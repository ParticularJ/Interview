#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Solution{
public:
  vector<vector<string>> groupAnagrams(vector<string>& strs){
    vector<vector<string>> res;
    unordered_map<string, int> mymap;
    if(strs.size()==0)return res;
    for(int i=0;i<strs.size();i++){
      string temp = strs[i];
      sort(temp.begin(),temp.end());
      if(mymap[temp]==0){
        // mymap为当前的res的size值，
        mymap[temp] = res.size();
        vector<string> temp1;
        temp1.push_back(strs[i]);
        res.push_back(temp1);
      }
      else{
        res[mymap[temp]].push_back(strs[i]);
      }
    }
    return res;
  }
};

int main(){
  Solution gA;
  vector<vector<string>> a;
  vector<string>  b = {"eat", "tea", "tan", "ate", "nat", "bat"};
  a = gA.groupAnagrams(b);
  for(auto b:a){
    for(auto c:b){
      cout<<c;
    }
  }
}
