#define MAXN 1000

int A[MAXN], B[MAXN];
int sA = 0, eA = -1, sB = 0, eB = -1;

void push(int num) {
    A[++ eA] = num;
    while(sB <= eB && B[eB] > num) {
        eB --;
    }
    B[++ eB] = num;
}

void pop() {
    if(sA <= eA) {
        if(sB <= eB && A[sA] == B[sB]) {
            sB ++;
        }
        sA ++;
    }
}

int get_min() {
    if(sB <= eB) {
        return B[sB];
    }
    return std::numeric_limits<int>::max();
}