#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

class Solution{
public:
  int lengthOfLongestSubstring2(string s){
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

int main(){
  string a = "abcabcbb";
  Solution lOLS;
  cout<<lOLS.lengthOfLongestSubstring1(a);
  return 0;
}
