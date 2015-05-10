// Modify get_val() accordingly

#define MAXN 1005
#define ALPHASIZE 26

class node {
    public:
    int len, suff;
    int child_cnt, occ;
    int nxt[ALPHASIZE];
} tree[MAXN];

int num, suff;

string s;

int get_val(char c) {
    return (c - 'a');
}

void init() {
    num = suff = 2;
    tree[1].len = -1, tree[1].suff = 1;
    tree[2].len = 0, tree[2].suff = 1;
}

//Check for false if a new node is created; number of new palindromes added
bool add(int pos) {
    int cur_suff = suff;
    int cur_len = 0;
    int val = get_val(s[pos]);
    while(1) {
        cur_len = tree[cur_suff].len;
        if(pos - cur_len - 1 >= 0 && s[pos] == s[pos - cur_len - 1]) {
            break;
        }
        cur_suff = tree[cur_suff].suff;
    }
    if(tree[cur_suff].nxt[val] != 0) {
        suff = tree[cur_suff].nxt[val];
        tree[suff].occ ++;
        return false;
    }
    suff = ++ num;
    tree[num].len = tree[cur_suff].len + 2;
    tree[num].occ ++;
    tree[cur_suff].nxt[val] = num;
    if(tree[num].len == 1) {
        tree[num].suff = 2;
        tree[num].child_cnt = 1;
        return true;
    }
    while(1) {
        cur_suff = tree[cur_suff].suff;
        cur_len = tree[cur_suff].len;
        if(pos - cur_len - 1 >= 0 && s[pos] == s[pos - cur_len - 1]) {
            tree[num].suff = tree[cur_suff].nxt[val];
            break;
        }
    }
    tree[num].child_cnt = 1 + tree[tree[num].suff].child_cnt;
    return true;
}

int main() {
    cin >> s;
    init();
    for(int i=0; i<s.size(); i++) {
        add(i);
        //Count number of palindrome substrings
        //ret += tree[suff].child_cnt;
    }
    //Count number of each palindrome substring occurrences
    /*
    for(int i=num; i>2; i--) {
        ret += tree[i].occ;
        tree[tree[i].suff].occ += tree[i].occ;
    }
    */
}
