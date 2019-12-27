class Solution {
public:
    int trie[1010][26];
    int cnt[1010], tot;

    void create(string st)
    {
        int len = st.length();
        int u = 0;
        for(int i = 0; i < len; i++)
        {
            if(trie[u][st[i]-'a'] == 0) trie[u][st[i]-'a'] = ++tot;
            u = trie[u][st[i]-'a'];
        }
        cnt[u]++;
    }
    
    string longestCommonPrefix(vector<string>& strs) {
        for(int i = 0; i < strs.size(); i++) {
            create(strs[i]);
        }
        string result;
        int u = 0, rear = 0;
        while(1) {
            int tot = 0;
            int temp = 0;
            for(int i = 0; i < 26; i++) {
                if(trie[u][i]) tot++, temp = i;
            }
            if(tot != 1 || cnt[u]) break;
            result += temp + 'a';
            u = trie[u][temp];
        }
        return result;
        }
};