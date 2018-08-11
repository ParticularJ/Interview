#include<iostream>

using namespace std;

typedef struct tower {
	int index;
	int val;
}tower;

bool compare(tower a, tower b) {
	return a.val < b.val;
}

int main() {
	int n, k, ai;
	cin >> n >> k;
	vector<int> A(n, 0);
	for (int i = 0; i < n; i++) {
		cin >> ai;
		tower.index = i;
		tower.val = ai;
	}
	vector<pair<int, int> > temp;
	while (k > 0) {
		sort(tower, tower + n, compare);
		A[0] = A[0] + 1;
		A[n - 1] = A[n - 1] - 1;
		temp.push_back(make_pair(A[n - 1].index, A[0].index));
		k--;
		if (A[0] == A[n - 1]) {
			cout << 0 << " " << k;
			for (int i = 0; i < k; i++) {
				cout << temp[k].first << " " << temp[k].second;
			}
		}
	}
	cout << tower[n - 1].val - tower[0].val << " " << 0 << endl;

	for (int i = 0; i < k; i++) {
		cout << temp[k].first << " " << temp[k].second;
	}
	return 0;
}