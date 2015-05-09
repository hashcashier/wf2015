// Modify get_val() accordingly

#define MAXN 1000
#define WORDSIZE 100
#define ALPHASIZE 26

int trie[MAXN * WORDSIZE][ALPHASIZE], node = 1;
bool flag[MAXN * WORDSIZE];

int get_val(char c) {
    return c - 'a';
}

void insert(string word) {
    int cur = 0, ind = 0, sz = word.size();
    while(ind < sz && trie[cur][get_val(word[ind])] != 0) {
        cur = trie[cur][get_val(word[ind])];
        ind ++;
    }
    for(int i=ind; i<sz; i++) {
        trie[cur][get_val(word[i])] = node;
        cur = node ++;
    }
    flag[cur] = true;
}

bool search(string word) {
    int cur = 0, ind = 0, sz = word.size();
    while(ind < sz && trie[cur][get_val(word[ind])] != 0) {
        cur = trie[cur][get_val(word[ind])];
        ind ++;
    }
    return !(ind < sz || flag[cur] == false);
}