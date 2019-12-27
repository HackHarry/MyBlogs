int lengthOfLastWord(char* s) {
    int len = strlen(s);
    int sum = 0, f = 0;
    for(int i = len-1; i >= 0; i--) {
        if(f && s[i] == ' ') break;
        if(s[i] != ' ') {
            sum++; 
            f = 1;
        }
    }
    return sum;
}