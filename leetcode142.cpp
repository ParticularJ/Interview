/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/


/*
˼·��
����ָ�룬���֮��һ��ָ���ͷ�ߣ�һ��ָ����������ߣ��ٴ�������Ϊ��ʼ�㡣
��ָ�룺 a + b  ��ָ�� a+b+c+b
�� 2(a + b)=(a+b+c+b)  ->  a = c
���Դ�����������ߣ��ʹ�ͷ��ʼ�ߣ��ٴ�������Ϊ������㡣
*/
class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		if (head == NULL || head->next == NULL)return NULL;
		ListNode* slow = head;
		ListNode* fast = head;
		ListNode* begin = head;
		while (fast->next&&fast->next->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) {
				while (begin != slow) {
					begin = begin->next;
					slow = slow->next;
				}
				return begin;
			}
		}
		return NULL;
	}
};