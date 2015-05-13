/*
Tree is 1-based
Tree can be extended to N-dimensions
*/

#define MAXN 1000

int N;
int bit[MAXN+1];
int bit2[MAXN+1][MAXN+1];

void update(int idx, int val) {
	for(int i=idx; i<=N; i+=(i & -i)) {
		bit[i] += val;
	}
}

int query(int idx) {
	int ret = 0;
	for(int i=idx; i>0; i-=(i & -i)) {
		ret += bit[i];
	}
	return ret;
}

int find(int val) {
	int idx = 0, num = (int) log2(N);
	int mask = (1 << num);
	while(mask != 0 && idx < N) {
		int nidx = idx + mask;
		if(val == bit[nidx]) {
			return nidx;
		}
		else if(val > bit[nidx]) {
			idx = nidx;
			val -= bit[nidx];
		}
		mask >>= 1;
	}
	return (val != 0) ? -1 : idx;
}

void update2(int x, int y, int val) {
	for(int i=x; i<=N; i+=(i & -i)) {
		for(int j=y; j<=N; j+=(j & -j)) {
			bit2[i][j] += val;
		}
	}
}

int query2(int x, int y) {
	int ret = 0;
	for(int i=x; i>0; i-=(i & -i)) {
		for(int j=y; j>0; j-=(j & -j)) {
			ret += bit[i][j];
		}
	}
	return ret;
}