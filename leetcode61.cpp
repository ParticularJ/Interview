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
	ListNode* rotateRight(ListNode* head, int k) {
		if (head == NULL || k == 0)return head;
		ListNode *temp = head;
		int count = 1;
		//统计长度
		while (temp->next) {
			temp = temp->next;
			count++;
		}
		// 成环
		temp->next = head;
		//要断的位置
		int index = k % count;
		// count-index 要挪动几次
		for (int i = 0; i < count - index; i++) {
			temp = temp->next;
		}
		ListNode *res = temp->next;
		temp->next = NULL;
		return res;
	}
};