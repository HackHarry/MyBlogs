int strStr(char* haystack, char* needle) {
    int lenh = strlen(haystack);
    int lenn = strlen(needle);
    if(lenh < lenn) return -1;
    if(lenn == 0) return 0;
    for(int k = 0; k <= lenh-lenn; k++) {
        int flag = 0, i = k, j = 0;
        while(i < lenh && j < lenn && haystack[i] == needle[j]) {
            i++; j++;
            if(j == lenn) flag = 1;
        }
        if(flag) return i-lenn;
    }
    return -1;
}