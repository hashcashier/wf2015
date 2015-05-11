// Modify get_val accordingly

#define ALPHASIZE 26

class node {
    public:
    int rev, alpha;
    int nxt[ALPHASIZE];
    vector<int> child, patts;

    node() {
        rev = -1;
        memset(nxt, 0, sizeof(nxt));
    }
};

vector<node> trie;

string text;
vector<string> patterns;

int get_val(char c) {
    return c - 'a';
}

void init() {
    trie.clear();
    node root;
    root.rev = 0;
    trie.push_back(root);
}

void insert(string word, int ind) {
    int cur = 0, sz = word.size();
    for(int i=0; i<sz; i++) {
        int val = get_val(word[i]);
        int nxt = trie[cur].nxt[val];
        if(nxt == 0) {
            node tmp;
            tmp.alpha = val;
            trie.push_back(tmp);
            int last_elem = (int)(trie.size() - 1);
            trie[cur].child.push_back(last_elem);
            trie[cur].nxt[val] = last_elem;
            nxt = last_elem;
        }
        cur = nxt;
    }
    trie[cur].patts.push_back(ind);
}

void create_revert() {
    queue<int> Q;
    int root = 0;
    for(int i=0; i<trie[root].child.size(); i++) {
        int child = trie[root].child[i];
        Q.push(child);
        trie[child].rev = root;
    }
    while(!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        for(int i=0; i<trie[cur].child.size(); i++) {
            int child = trie[cur].child[i];
            Q.push(child);
            int cur_rev = trie[cur].rev;
            int nxt = trie[cur_rev].nxt[trie[child].alpha];
            while(1) {
                if(nxt == 0) {
                    if(cur_rev == root) {
                        trie[child].rev = root;
                        break;
                    }
                    cur_rev = trie[cur_rev].rev;
                }
                else {
                    trie[child].rev = nxt;
                    for(int j=0; j<trie[nxt].patts.size(); j++) {
                        trie[child].patts.push_back(trie[nxt].patts[j]);
                    }
                    break;
                }
            }
        }
    }
}

void build_aho() {
    init();
    for(int i=0; i<patterns.size(); i++) {
        insert(patterns[i], i);
    }
    create_revert();
}

void search() {
    int root = 0, ind = 0, last = -1;
    int cur = root;
    while(ind < text.size()) {
        int val = get_val(text[ind]);
        int nxt = trie[cur].nxt[val];
        if(nxt == 0) {
            if(cur == root) {
                ind ++;
            }
            else {
                cur = trie[cur].rev;
            }
        }
        else {
            cur = nxt;
            ind ++;
        }
        //Check to remove duplicates
        if(last != ind) {
            for(int i=0; i<trie[cur].patts.size(); i++) {
                int patt_idx = trie[cur].patts[i];
                //cout << patterns[patt_idx] << " at " << (ind - patterns[patt_idx].size()) << endl;
            }
        }
        last = ind;
    }
}