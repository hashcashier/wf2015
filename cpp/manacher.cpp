#define MAXN 100000

string trans;
int P[2*MAXN+3];

string orig;

string normalize(string s) {
    string ret = "";
    if(s.size() == 0) {
        ret += "^$";
    }
    ret += "^";
    for(int i=0; i<s.size(); i++) {
        ret += "#";
        ret += s[i];
    }
    ret += "#$";
    return ret;
}

void manacher() {
    trans = normalize(orig);
    int C = 0, R = 0;
    for(int i=1; i<trans.size()-1; i++) {
        int mirror = 2*C - i;
        P[i] = (R > i) ? min(R - i, P[mirror]) : 0;
        while(trans[i + 1 + P[i]] == trans[i - 1 - P[i]]) {
            P[i] ++;
        }
        if(i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }
}