/**
* Definition for singly-linked list with a random pointer.
* struct RandomListNode {
*     int label;
*     RandomListNode *next, *random;
*     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
* };
*/

/*
 ��ʵ����һ���������⣬����ֻҪ��map����Ӧ��ӳ�䣬��������
 ��Ҫ�����Ƿ�������⡣
 map ǰһ��Ϊӳ����ֵ����һ��Ϊԭʼֵ����
 �µĽڵ�Ҫ���µĽڵ�ӳ��
*/
class Solution {
public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		map<RandomListNode *, RandomListNode *> f;
		if (head == NULL)
			return NULL;
		f[head] = new RandomListNode(head->label);
		f[head->next] = head->next;
		for (RandomListNode * i = head; i; i->next) {
			if (i->next) {
				if (f[i->next] == 0) {
					f[i->next] = new RandomListNode(i->next->label);
				}
				f[i]->next = f[i->next];
			}
			if (i->random) {
				if (f[i->random] == 0) {
					f[i->random] = new RandomListNode(i->random->label);
				}
				f[i]->random = f[i->random];
			}
		}
		return f[head];
	}
};