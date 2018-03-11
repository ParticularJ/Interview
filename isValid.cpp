#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<stack>
// 首先要想到字典，因为符号的对应关系
// 其次要想到栈的先进后出关系
// 找出满足要求的 "()[]{}""([])"关系，相当于下一个元素与栈顶元素比较
using namespace std;

class Solution{
public:
    bool isValid(string s){
        map<char, char> mapsign={
          {'(',')'},
          {'[',']'},
          {'{','}'}
        };
        stack<char> aux;
        for(int i=0;i!=s.length();++i){
            if(s[i]=='(' || s[i]=='[' || s[i]=='{')
                aux.push(s[i]);
            else if(aux.empty() || mapsign[aux.top()] != s[i])
                return false;
            else{
                cout<<aux.size()<<endl;
                aux.pop();
                cout<<aux.size()<<endl;
              }
        }
        return aux.empty();
    }
};

int main(){
    Solution valid;
    string s="(){}[]";
    cout<< valid.isValid(s);
}
