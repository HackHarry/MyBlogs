class Solution:
    def climbStairs(self, n: int) -> int:
        x = 1
        y = 1
        for i in range(1, n):
            x = x + y
            x, y = y, x
        return y