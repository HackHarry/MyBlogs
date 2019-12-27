class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        nums3 = [x for x in nums1]
        i = 0
        j = 0
        k = 0
        while i < n and j < m:
            if nums2[i] <= nums3[j]:
                nums1[k] = nums2[i]
                i = i + 1
            else:
                nums1[k] = nums3[j]
                j = j + 1
            k = k + 1
        while i < n:
            nums1[k] = nums2[i]
            k = k + 1
            i = i + 1
        while j < m:
            nums1[k] = nums3[j]
            k = k + 1
            j = j + 1
        