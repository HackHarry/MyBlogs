# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def mergeTwoLists(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        if l1 == None:
            return l2
        if l2 == None:
            return l1
        if l1.val > l2.val:
            p = l2
            q = l1
            flag = True
        else:
            p = l1
            q = l2
            flag = False
        while p.next!=None and q!=None:
            if p.next.val > q.val:
                r, q = q, q.next
                r.next, p.next = p.next, r
            p = p.next
        if q!=None:
            p.next = q
        if flag:
            return l2
        else:
            return l1