#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

class Solution{
public:
  // int lengthOfLongestSubstring(string s){
  //   int rea=0;
  //   int size = s.size();
  //   if(!size)return res;
  //   unordered_map<int, int> mymap;
  //   int begin=0,end = 0;
  //   for(int i=0;i<size;i++){
  //     mymap[s[i]-'a']++;
  //   }
  //   for(int i=0;i<size;i++){
  //     if(mymap[s[i]-'a'])
  //   }
  // }
public:
  int lengthOfLongestSubstring(string s){
    vector<int> dict(256, -1);
    int size=s.size();
    int maxlen=0,start=-1;
    for(int i=0;i<size;i++){
      if(dict[s[i]]>start)
          start = dict[s[i]];
      dict[s[i]]=i;
      maxlen = max(maxlen, i-start);
    }
    return maxlen;
  }
};
