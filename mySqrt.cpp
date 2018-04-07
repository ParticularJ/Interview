#include<iostream>
#include<vector>
#include<string>
#include<iterator>

using namespace std;

//这道题要找x的平方根，x的平方根肯定小于x/2。要在[1,x/2]有序序列当中找一个数，用二分法：
//借助一个小结论，任何一个数的square都在大于等于1，小于x/2+1。很容易反证。
//mid 要使用 long型，否则会溢出
//可以直接从x/2开始

class Solution{
public:
  int mySqrt(int x){
    if(x==0) return 0;
    if(x==1) return 1;
    double low=0,high=x/2;
    while(low<=high){
      long mid = (low+high)/2;
      if(mid*mid == x) return static_cast<int>(mid);
      else if(mid*mid < x) low = mid+1;
      else if(mid*mid > x) high = mid-1;
      }
    return static_cast<int>(high);
  }
};

void main(){
  Solution ms;
  int x=5;
  cout<<ms.mySqrt(x);
}
