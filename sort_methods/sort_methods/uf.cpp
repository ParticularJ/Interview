/*
并查集：
主要支持两个操作
1、并 union(p, q) 
2、 查find(p) ,查询在哪个组中
用来回答
isConnected(p, q)

比如如下一个数组
id 0 1 2 3 4 5 6 7
   0 1 0 1 0 1 0 1

如何查找是否相连， id对应的值想到等即相连

*/


#include<iostream>
#include<cassert>
using namespace std;

class UnionFind {
private:
	// 开辟数组空间
	int* id;
	// 总共多少个数
	int count;
public:
	// 构造函数
	UnionFind(int n) {
		count = n;
		id = new int[n];
		for (int i = 0; i < count; i++) {
			id[i] = i;
		}
	}
	~UnionFind(){
		delete [] id;
	}
	// 查找组
	int find(int p) {
		assert(p >= 0 && p < count);
		return id[p];
	}
	
	
	// 判断是否相连
	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	// 并集操作
	void unionElements(int p, int q) {
		int pID = find(p);
		int qID = find(q);
		if(pID == qID)
			return;
		// 遍历，将等于pID的全部修改
		for (int i = 0; i < count; i++) {
			if (id[i] == pID)
				id[i] = qID;
		}
	}
};



/*
改进， 将一个节点的父节点指向另外一个的父节点
并且保证少的父节点指向多的父节点
*/

class UnionFind2 {
private:
	// 根节点
	int* parent;
	// 表示以i为根中的元素个数
	int* size;
	// 以高度来判别
	int* rank;
	int count;
public:
	UnionFind2(int n) {
		count = n;
		parent = new int[count];
		size = new int[count];
		rank = new int[count];
		for (int i = 0; i < count; i++) {
			parent[i] = i;
			size[i] = 1;
			rank[i] = 1;
		}
	}

	~UnionFind2(){
		delete[] parent;
		delete[] size;
		delete[] rank;
	}

	int find(int p) {
    // 路径压缩，没有找到的话就跳一步
	/*	while (p != parent[p]) {
			parent[p] = parent[parent[p]];
			p = parent[p];
		}
		return p;*/
	// 路径压缩优化，都指向统一个父亲节点
		if (p != parent[p]) {
			parent[p] = find(parent[p]);
		}
		return parent[p];

	}

	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	void unionElements(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot)
			return;
		
		
		// 否则的话将size小的指向size大的根,维护他的size
	    // 以size维护
		if (size[pRoot] > size[qRoot]) {
			parent[qRoot] = pRoot;
			size[pRoot]+= size[qRoot];
		}
		else {
			parent[pRoot] = qRoot;
			size[qRoot]+= size[pRoot];
		}

		// 以rank维护
		if (rank[pRoot] > rank[qRoot])
			parent[qRoot] = pRoot;
		else if (rank[pRoot] < rank[qRoot])
			parent[pRoot] = qRoot;
		else {
			parent[pRoot] = qRoot;
			rank[qRoot] += 1;
		}

	}
};