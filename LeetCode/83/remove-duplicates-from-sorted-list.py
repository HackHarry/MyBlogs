# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def deleteDuplicates(self, head: ListNode) -> ListNode:
        if head == None:
            return head
        p = head
        while p.next != None:
            if p.next.val == p.val:
                p.next = p.next.next
            else:
                p = p.next
        return head        
        