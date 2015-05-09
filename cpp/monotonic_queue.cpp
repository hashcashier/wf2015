/*
This implementation has the features of:
1. Finding current minimum
2. Popping back from the array
*/

#define MAXN 1005

int A[MAXN], B[MAXN];
int cntA, cntB;
 
void push(int num) {
    A[cntA ++] = num;
    if(cntB == 0 || num <= B[cntB - 1]) {
        B[cntB ++] = num;
    }
}
 
void pop() {
    if(cntA > 0) {
        if(cntB > 0 && A[cntA - 1] == B[cntB - 1]) {
            cntB --;
        }
        cntA --;
    }
}
 
int get_min() {
    return B[cntB - 1];
}