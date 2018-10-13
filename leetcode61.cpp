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
		//ͳ�Ƴ���
		while (temp->next) {
			temp = temp->next;
			count++;
		}
		// �ɻ�
		temp->next = head;
		//Ҫ�ϵ�λ��
		int index = k % count;
		// count-index ҪŲ������
		for (int i = 0; i < count - index; i++) {
			temp = temp->next;
		}
		ListNode *res = temp->next;
		temp->next = NULL;
		return res;
	}
};