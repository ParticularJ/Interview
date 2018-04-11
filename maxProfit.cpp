#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>


using namespace std;

// 动态规划，我们每次记住最小的，
// 遍历数组，减去最小的即可，

class Solution{
public:
  int maxProfit(vector<int>& prices){
    if(!prices.size()) return 0;
    int profit=0;
    int buy=INT_MAX;
    for(int i=0;i<prices.size()-1;i++){
      buy=min(buy, prices[i]);
      profit=max(profit,prices[i] - buy);
    }
    return profit;
  }
};

void main(){
  Solution mP;
  vector<int> a = {7, 1, 5, 3, 6, 4};
  cout<<mP.maxProfit(a);
}
