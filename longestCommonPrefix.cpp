#include<iostream>
#include<vector>
#include<string>

using namespace std;

// 首先确定最大的字符串长度
// 分别取出第一个字符串第一个字符，然后与所有字符串每个字符进行比较
// 需要一个标志位判断是否跳出循环

class Solution{
public:
    string longestCommonPrefix(vector<string>& strs){
        if(strs.empty()) return "";
        string ans="";
        int max=INT_MAX;
        //确定最长的字符串长度
        for(auto& s:strs){
            max=(s.length() < max) ? s.length():max;
        }
        for(int i=0;i!=max;i++){
            bool flag=true;
            char x=strs[0][i];
            cout<<x<<endl;
            // 注意break的使用
            for(auto& s:strs){
                if(s[i]!=x){
                  flag=false;
                  break;
                }
            }
            if(flag==false) return ans;
            ans += x;
        }
        return ans;
    }
};

int main(){
    Solution lcp;
    vector<string> a={"abcdfefe","abd","abe"};
    cout<<lcp.longestCommonPrefix(a);
}
