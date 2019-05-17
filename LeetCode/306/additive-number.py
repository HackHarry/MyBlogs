class Solution:
    def isAdditiveNumber(self, num: str) -> bool:
        n = len(num)
        for i in range(1,n//2+1):
            for j in range(i+1, (i+n)//2+1):
                x = int(num[:i])
                if str(x) != num[:i]:
                    continue
                y = int(num[i:j])
                if str(y) != num[i:j]:
                    continue
                s = num[:j]
                while n > len(s):
                    x, y = y, x+y
                    s = s + str(y)
                if num == s:
                    return True
        return False
                