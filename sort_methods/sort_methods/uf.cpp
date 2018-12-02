/*
���鼯��
��Ҫ֧����������
1���� union(p, q) 
2�� ��find(p) ,��ѯ���ĸ�����
�����ش�
isConnected(p, q)

��������һ������
id 0 1 2 3 4 5 6 7
   0 1 0 1 0 1 0 1

��β����Ƿ������� id��Ӧ��ֵ�뵽�ȼ�����

*/


#include<iostream>
#include<cassert>
using namespace std;

class UnionFind {
private:
	// ��������ռ�
	int* id;
	// �ܹ����ٸ���
	int count;
public:
	// ���캯��
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
	// ������
	int find(int p) {
		assert(p >= 0 && p < count);
		return id[p];
	}
	
	
	// �ж��Ƿ�����
	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	// ��������
	void unionElements(int p, int q) {
		int pID = find(p);
		int qID = find(q);
		if(pID == qID)
			return;
		// ������������pID��ȫ���޸�
		for (int i = 0; i < count; i++) {
			if (id[i] == pID)
				id[i] = qID;
		}
	}
};



/*
�Ľ��� ��һ���ڵ�ĸ��ڵ�ָ������һ���ĸ��ڵ�
���ұ�֤�ٵĸ��ڵ�ָ���ĸ��ڵ�
*/

class UnionFind2 {
private:
	// ���ڵ�
	int* parent;
	// ��ʾ��iΪ���е�Ԫ�ظ���
	int* size;
	// �Ը߶����б�
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
    // ·��ѹ����û���ҵ��Ļ�����һ��
	/*	while (p != parent[p]) {
			parent[p] = parent[parent[p]];
			p = parent[p];
		}
		return p;*/
	// ·��ѹ���Ż�����ָ��ͳһ�����׽ڵ�
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
		
		
		// ����Ļ���sizeС��ָ��size��ĸ�,ά������size
	    // ��sizeά��
		if (size[pRoot] > size[qRoot]) {
			parent[qRoot] = pRoot;
			size[pRoot]+= size[qRoot];
		}
		else {
			parent[pRoot] = qRoot;
			size[qRoot]+= size[pRoot];
		}

		// ��rankά��
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