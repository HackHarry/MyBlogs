class Solution:
    def addBinary(self, a: str, b: str) -> str:
        l1 = list(a)
        len1 = len(l1)
        l2 = list(b)
        len2 = len(l2)
        s = ""
        x = 0
        while len1>0 and len2>0:
            x = int(l1[len1-1]) + int(l2[len2-1]) + x
            s = str(x%2) + s
            x = x // 2
            len1 = len1 - 1
            len2 = len2 - 1
        while len1 > 0:
            x = int(l1[len1-1]) + x
            s = str(x%2) + s
            x = x // 2
            len1 = len1 - 1
        while len2 > 0:
            x = int(l2[len2-1]) + x
            s = str(x%2) + s
            x = x // 2
            len2 = len2 - 1
        if len2 == 0 and len1 == 0 and x != 0:
            s = str(x) + s
        return s





class Solution:
    def addBinary(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: str
        """
        return bin(int(a,2)+int(b,2))[2:]