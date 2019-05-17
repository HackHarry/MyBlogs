class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int len = digits.size();
        int f = 1, i = 0;
        while(f && i < len) {
            if(digits[i++] != 9) f = 0;
        }
        if(f) {
            vector<int> ans;
            ans.push_back(1);
            for(i = 0; i < len; i++) ans.push_back(0);
            return ans;
        }
        int temp = 1; i = len;
        while(temp && i--) {
            digits[i] += temp;
            temp = digits[i] / 10;
            digits[i] %= 10;
        }
        return digits;
    }
};