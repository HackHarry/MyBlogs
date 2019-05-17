int reverse(int x) {
    int f = 0;
    if(x == -2147483648) return 0;
    if(x < 0) f = 1, x = -x;
    int result = 0;
    while(x) {
        if(result > INT_MAX/10 || (result == INT_MAX/10 && x%10 > 7)) return 0;
        result = result*10 + x%10;
        x /= 10;
    }
    if(f) result = -result;
    return result;
}