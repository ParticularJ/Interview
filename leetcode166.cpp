#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

class Solution{
public:
  string fractionToDecimal(int numerator, int denominator){
    if(numerator==0)return "0";
  //  cout<<"fi"<<endl;
    string res="";
    long long num = numerator;
    long long den = denominator;
    int sign = 1;
    if(num<0){
      sign = -sign;
      num=-num;
    }
    if(den<0){
      sign = -sign;
      den = -den;
    }
    long long quotient = num / den;
    long long mod = num % den;
  //  cout<<quotient<<" "<<mod;
    char temp[20];
    sprintf(temp, "%lld", quotient);
    res += string(temp);
    if(mod!=0){
      res+=".";
      map<pair<int, int>, int> mymap;//记录商，模，还有位置，方便记录
      string n="";
      for(int index=1;;index++){
        mod*=10;
        long long a = mod/den;  // 商
        long long b = mod%den;  // 模
        // 只有商和模相等时，才不为0
        cout<<"a:"<<a<<"b:"<<b<<endl;
        cout<<"map:"<<mymap[make_pair(a, b)]<<endl;
        if(mymap[make_pair(a, b)]!=0){
          long long l = mymap[make_pair(a,b)]-1; // 记录前一位，因为从下一位开始循环
          res += n.substr(0, l);
          res  = res+"(";
          res += n.substr(l, n.size()-l);
          res  = res+")";
          break;
        }
        else{
          mymap[make_pair(a, b)]=index;
        }
        n += char('0'+a);
        if(mod==0){
          res+=n;
          break;
        }
        mod = b;
    }

    }
    return (sign==-1)?("-"+res):res;
  }
};


int main(){
  int a,b;
  cout<<"input a, b"<<endl;
  cin>>a;
  cin>>b;
  Solution fTD;
  cout<<fTD.fractionToDecimal(a,b);
  return 0;
}
