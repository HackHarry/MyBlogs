class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        x = sum(nums)
        y = 0
        a = 0
        t = 0
        for i in range(1,len(nums)):
            if i in nums:
                y = y + i
            else:
                a = a + 1
        t = int((x-y)/(a+1))
        return t




class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        lnum = 1
        rnum = len(nums)
        while lnum+1 < rnum:
            snum = 0
            mnum = int((lnum+rnum)/2)
            for num in nums:
                if num < mnum and num >= lnum:
                    snum = snum + 1
            if snum > mnum-lnum:
                rnum = mnum
            else:
                lnum = mnum
        return lnum




class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        slow = nums[0]
        fast = nums[nums[0]]
        while slow != fast:
            slow = nums[slow]
            fast = nums[nums[fast]]
        fast = 0
        while nums[slow] != nums[fast]:
            slow = nums[slow]
            fast = nums[fast]
        return nums[slow]