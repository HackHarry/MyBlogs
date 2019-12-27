class Solution:
    def countAndSay(self, n):
        """
        :type n: int
        :rtype: str
        """
        if n == 1:
            return "1"
        if n == 2:
            return "11"
        s = "11"
        for i in range(2, n):
            num = 1
            s1 = ""
            for j in range(1, len(s)):
                if s[j] == s[j-1]:
                    num = num + 1
                else:
                    s1 = s1 + str(num) + s[j-1]
                    num = 1
            s = s1 + str(num) + s[len(s)-1]
        return s