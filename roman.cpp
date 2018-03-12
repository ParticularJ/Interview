#include<iostream>
#include<string>
#include<map>
using namespace std;


class Solution{
public:
    int romanToInt(string s){
        string a=s;
        cout<<a<<' '<<a.length();
        if(s.empty()) return 0;
        map<char, int> mapchar={
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        int result=0;
        for(int i=0;i!=s.length()-1;++i){
            if(mapchar[s[i]]<mapchar[s[i+1]]){
                result -= mapchar[s[i]];
            }
            else{
                result += mapchar[s[i]];
            }
        }
        // s.back()获取最后一个string的值
        return result += mapchar[s.back()];
    }
};

int main(){
    Solution roman;
    cout<<roman.romanToInt("DCXXI");
}
