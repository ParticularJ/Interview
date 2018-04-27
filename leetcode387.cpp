#include<iostream>
#include<map>

using namespace std;

class Solution{
public:
  int firstUniqChar(string s){
    map<char,int> mymap;
    for(int i=0;i<s.length();i++){
      mymap[s[i]]++;
    }
    for(map<char, int>::iterator iter=mymap.begin();iter!=mymap.end();iter++){
      cout<<iter->first<<":"<<iter->second<<endl;
    }
    return 0;
  }
};

int main(){
  string s = "leetcode";
  Solution fU;
  cout<< fU.firstUniqChar(s);
}
