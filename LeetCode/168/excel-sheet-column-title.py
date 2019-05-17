class Solution:
    def convertToTitle(self, n):
        """
        :type n: int
        :rtype: str
        """
        if n < 27:
            return str(chr((n-1)+ord('A')))
        st = ""
        while n > 0:
            n = n - 1
            st = str(chr(n%26+ord('A'))) + st
            n = n // 26
        return st