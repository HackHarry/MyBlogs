int f(char c) {
    if(c == 'I') return 1;
    if(c == 'V') return 5;
    if(c == 'X') return 10;
    if(c == 'L') return 50;
    if(c == 'C') return 100;
    if(c == 'D') return 500;
    if(c == 'M') return 1000;
    return 0;
}

int romanToInt(char* s) {
    int len = strlen(s);
    if(len == 0) return 0;
    if(len == 1) return f(s[0]);
    int sum = 0;
    for(int i = 0; i < len-1; i++) {
        if(f(s[i+1]) <= f(s[i])) sum += f(s[i]);
        else sum -= f(s[i]);
    }
    sum += f(s[len-1]);
    return sum;
}