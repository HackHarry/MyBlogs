class Solution:
    def findMinDifference(self, timePoints: List[str]) -> int:
        if len(timePoints) >= 1440:
            return 0
        def change(timestr : str) -> int:
            return int(timestr.split(":")[0])*60+int(timestr.split(":")[1])
        for i in range(len(timePoints)):
            timePoints[i] = change(timePoints[i])
        l = sorted(timePoints)
        mint = 24*60+l[0]-l[-1]
        for i in range(1,len(timePoints)):
            mint = min(mint, l[i]-l[i-1])
            if mint == 0:
                return 0
        return mint