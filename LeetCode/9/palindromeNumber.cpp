bool isPalindrome(int x) {
    if(x < 0) return false;
    int x1 = x, x2 = 0;
    while(x) {
        x2 = x2*10 + x%10;
        x /= 10;
    }
    if(x1 == x2) return true;
    return false;
}