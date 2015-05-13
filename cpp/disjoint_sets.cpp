int N;
vector<int> pset, wset;

int findSet(int x) {
    if(pset[x] != x) {
        pset[x] = findSet(pset[x]);
    }
    return pset[x];
}

bool isSameSet(int x, int y) {
    return findSet(x) == findSet(y);
}

void unionSet(int x, int y) {
    int i = findSet(x);
    int j = findSet(y);
    if(i == j) {
        return;
    }
    if(wset[i] < wset[j]) {
        pset[i] = j;
    }
    else {
        pset[j] = i;
        wset[i] += (wset[i] == wset[j]);
    }
}

void init() {
    wset.assign(N, 0);
    pset.assign(N, 0);
    for(int i=0; i<N; i++) {
        pset[i] = i;
    }
}
