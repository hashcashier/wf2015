#define MAXN 100000

string text, pattern;

int b[MAXN];
vector<int> found;

void kmpPreprocess() {
    int i = 0, j = -1;
    b[0] = -1;
    while(i < pattern.size()) {
        while(j >= 0 && pattern[i] != pattern[j]) {
            j = b[j];
        }
        i ++;
        j ++;
        b[i] = j;
    }
}

void kmpSearch() {
    found.clear();
    int i = 0, j = 0;
    while(i < text.size()) {
        while(j >= 0 && text[i] != pattern[j]) {
            j = b[j];
        }
        i ++;
        j ++;
        if(j == pattern.size()) {
            found.push_back(i - j);
            j = b[j];
        }
    }
}