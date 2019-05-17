class Solution:
    def kSmallestPairs(self, nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:
        if len(nums1) == 0 or len(nums2) == 0:
            return []
        L = [[x,y,x+y] for x in nums1 for y in nums2]
        L.sort(key = lambda x:x[2])
        k = min(len(L),k)
        nums = [[0,0]]*k
        for i in range(k):
            nums[i] = [L[i][0],L[i][1]]
        return nums