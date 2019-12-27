bool isValid(char* s) {
    int len = strlen(s);
    char sta[10000];
    int top = 0;
    for(int i = 0; i < len; i++) {
        switch(s[i]) {
            case '(':
            case '[':
            case '{':
                sta[top++] = s[i];
                break;
            case ')':
                if(top == 0) return false;
                if(sta[top-1] == '(') top--;
                else return false;
                break;
            case ']':
                if(top == 0) return false;
                if(sta[top-1] == '[') top--;
                else return false;
                break;
            case '}':
                if(top == 0) return false;
                if(sta[top-1] == '{') top--;
                else return false;
                break;
            default: return false;
        }
    }
    if(top == 0) return true;
    return false;
}