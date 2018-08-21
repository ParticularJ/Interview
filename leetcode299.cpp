class Solution {
public:
	string getHint(string secret, string guess) {
		int size = secret.size();
		if (size == 0)return "0A0B";
		string res = "";

		vector<int> cnt(10, 0);
		int bulls = 0, cows = 0;

		for (int i = 0; i < size; i++) {
			if ((guess[i] - '0') == (secret[i] - '0')) {
				bulls++;
			}else
			// ͳ��ԭ���ַ�����δ���ֵĴ���
			cnt[secret[i] - '0']++;
		}

		for (int i = 0; i<size; i++) {
			// �Ͳ²�ıȽϣ�
			if ((guess[i] - '0') != (secret[i] - '0') && cnt[guess[i] - '0']>0) {
				cnt[guess[i] - '0']--;
				cows++;
			}
		}
		res = to_string(bulls) + "A" + to_string(cows) + "B";
		return res;
	}
};