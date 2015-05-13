#define MAXN 1000

int N;
int bit[MAXN+1][MAXN+1];

void update(int x, int y, int val) {
	for(int i=x; i<=N; i+=(i & -i)) {
		for(int j=y; j<=N; j+=(j & -j)) {
			bit[i][j] += val;
		}
	}
}

int query(int x, int y) {
	int ret = 0;
	for(int i=x; i>0; i-=(i & -i)) {
		for(int j=y; j>0; j-=(j & -j)) {
			ret += bit[i][j];
		}
	}
	return ret;
}