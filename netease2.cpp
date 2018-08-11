#include<iostream>
#include<vector>
using namespace std;
int N;
int Hi, Mi;
int X;
int A, B;



int main() {
	cin >> N;
	vector<int> clock(N, 0);
	for (int i = 0; i < N;i++) {
		cin >> Hi>>Mi;
		clock[i] = Hi * 60 + Mi;
	}
	cin >> X;
	cin >> A >> B;
	int deadline = A * 60 + B;
	sort(clock.begin(), clock.end());
	int i;
	for (i = 0; i < clock.size(); i++) {
		if (X + clock[i] > deadline)break;
	}
	int index = --i;
	cout << clock[index] / 60 << " " << (clock[index] - (clock[index] / 60) * 60);
	return 0;
}