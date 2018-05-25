#include<iostream>
#include<vector>
#include<string>

class Solution{
public:
  string fractionToDecimal(int numerator, int denominator){
    if(numerator==0)return "0";
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
    
  }
};


int main(){
  int a,b;
  cin>>a,b;
  Soluton fTD;
  fTD.fractionToDecimal(a,b);
  return 0;
}
