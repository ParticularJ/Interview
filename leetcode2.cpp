/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode dummy(0);
		ListNode* tail = &dummy;
		ListNode *p1 = l1, *p2 = l2;
		int sum = 0;
		while (p1 != NULL || p2 != NULL) {
			if (p1 != NULL) {
				sum += p1->val;
				p1 = p1->next;
			}
			if (p2 != NULL) {
				sum += p2->val;
				p2 = p2->next;
			}
			// 新建一个节点
			tail->next = new ListNode(sum % 10);
			tail = tail->next;
			// 判断有没有进位
			sum /= 10;
		}
		// 判断最后的进位
		if (sum == 1)tail->next = newListNode(1);
		return dummy.next;
	}
};


jglknendpl
ocymmvwtox
vebkekzfdh
ykknufqdkn
tnqvgfbahs
ljkobhbxkv
yictzkqjqy
dczuxjkgec
dyhixdttxf
qmgksrkyvo
pwprsgoszf
tuhawflzjy
uyrujrxluh
zjvbflxgco
vilthvuihz
ttzithnsqb
dxtafxrfrb
lulsakrahu
lwthhbjcsl
ceewxfxtav
ljpimaqqlc
brdgtgjryj
ytgxljxtra
vwdlnrraux
plempnbfeu
sgtqzjtzsh
wieutxdytlrrqvyemlyzolhbkzhyfyttevqnfvmpqjngcnazmaagwihxrhmcibyfkccyrqwnzlzqeuenhwlzhbxqxerfifzncimwqsfatudjihtumrtjtggzleovihifxufvwqeimbxvzlxwcsknksogsbwwdlwulnetdysvsfkonggeedtshxqkgbhoscjgpiel