#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

//思路:最短路径的方法
//构建图
//之后使用求解最短路径的算法SPFA


class Solution{
public:
  int diff(string s, string e){
    int cnt=0;
    for(int i=0;i<s.size();i++){
      if(s[i]!=e[i])cnt+=1;
    }
    return cnt;
  }
  int ladderLength(string beginWord, string endWord, vector<string>& wordList){
    int size = wordList.size();
    //构建图，就要构建边，由于有beginword 和endword,边为size+2
    vector<vector<int> > edge(size+2, vector<int>(size+2, 999));
    // 判断终止词的是不是在字典集里
    bool can_arrive = false;
	if (diff(beginWord, endWord) == 1) {
		edge[size].push_back(size + 1);
	}
    for(int i=0;i<size;i++){
      for(int j=i+1;j<size;j++){
        if(diff(wordList[i], wordList[j])==1){
          edge[i].push_back(j);
          edge[j].push_back(i);
        }
      }
      //如果重点不在list里面
      if(diff(beginWord, wordList[i])==1)
        edge[size].push_back(i);
      int temp = diff(endWord, wordList[i]);
      if(temp==0)can_arrive=true;
      // 如果不同就加入一条边
      if(temp==1)edge[i].push_back(size+1);
    }
    if(!can_arrive)return 0;

    //最短路径的求法， SPFA
    queue<int> que;
    vector<int> dist(size+2, (1<<31)-1);
    que.push(size);
    dist[size]=1;
    for(;que.size()>0;que.pop()){
      int n = que.front();
      int d = dist[n];
      for(auto dest:edge[n]){
        if(dist[dest]>d+1){
          dist[dest]=d+1;
          que.push(dest);
          if(dest==size+1)
            return dist[dest];
        }
      }
    }

	// dijkstra 算法：
	// 初始化距离
	vector<int> dist(size + 2, (1 << 31) - 1);
	// 确定是否遍历该顶点
	vector<bool> flag(size + 2, 0);
	// 统计上一步点的dist,
	int lastVisited = 0;
	int start = size;
	flag[size] = 1;
	
	
	for (int i = 0; i < size + 1; i++) {
		for (int j = 0; j < size + 2; j++) {
			if (flag[j] == 0) {
				if (edge[start][j] != 0) {
					int curr_dis = 1 + lastVisited;
					if (dist[start] > curr_dis) {
						dist[start] = curr_dis;
					}
				}
			}
		// 找出第一个未被遍历的点
			int minIndex = 0;
			while (flag[minIndex] == 1)minIndex++;
			for（int j = minIndex; j < size + 2; j++ ）{
				if (flag[j] == 0 && dist[j] == dist[size]) {
					minIndex = j;
				}
			}
			lastVisited = dist[minIndex];
			start = minIndex;
			flag[minIndex] = 1;
		}
	}
    return dist[size+1];
  }
};



