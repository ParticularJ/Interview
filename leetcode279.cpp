#include<iostream>
#include<vector>
#include<queue>

// 我们需要维护一个数组，用来记录每一次平方之后的值
// 其次，我们需要一个队列，因为队列可以先进先出，这样每次
// 取队列的首元素，我们可以对比下一次的平方数
// 主要使用广度优先遍历

using namespace std;

class Solution{
public:
  int numSquares(int n){
	  assert(n > 0);
	  // 记录当前值和步数
	  queue<pair<int, int> > q;
	  q.push(make_pair(n, 0));
	  vector<bool> visited(n + 1, false);
	  visited[n] = true;
	  while (q.size()) {
		  int value = q.front().first;
		  int step = q.front().second;
		  q.pop();
		  for (int i = 1;; i++) {
			  int num = value - i*i;
			  if (num < 0)
				  break;
			  if (num == 0)
				  return step + 1;
			  if (visited[num] == false) {
				  q.push(make_pair(num, step + 1));
				  visited[num] = true;
			  }
		  }
	  }
  }
};

int main(){
  Solution nS;
  int a = 12;
  cout<<nS.numSquares(a)<<endl;
  return 0;
}
