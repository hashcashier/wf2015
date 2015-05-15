/*
indices are 0-based
prev: index of first element in current bucket
next: index of first element in next bucket
*/

#define MAXN 10000
#define SQRT 100

int bucket[SQRT][SQRT];
int ind[MAXN], prev[MAXN], next[MAXN];

int N, sq, last_sz;
int arr[MAXN];

void decompose() {
	sq = sqrt(N);
	int tmp = N - (sq * sq);
	if(sq * sq < N) sq ++;
	last_sz = (tmp == 0) ? sq : N % sq;
	for(int i=0; i<N; i++) {
		ind[i] = i / sq;
		next[i] = ind[i] * sq + sq;
		prev[i] = next[i] - sq;
	}
	for(int i=0; i<N; i++) {
		bucket[ind[i]][i%sq] = arr[i];
	}
	sort(bucket[sq-1], bucket[sq-1]+last_sz);
	for(int i=0; i<sq-1; i++) {
		sort(bucket[i], bucket[i]+sq);
	}
}

void update(int x, int val) {
	int pos = ind[x];
	int sz = (pos == sq-1) ? last_sz : sq;
	int idx;
	for(int i=0; i<sz; i++) {
		if(bucket[pos][i] == arr[x]) {
			idx = i;
			break;
		}
	}
	arr[x] = val;
	if(val != bucket[pos][idx]) {
		if((idx == sz-1 && val > bucket[pos][idx]) || (idx == 0 && val < bucket[pos][idx])) {
			bucket[pos][idx] = val;
		}
		else if(val > bucket[pos][idx]) {
			for(int i=idx+1; i<sz; i++) {
				if(val <= bucket[pos][i]) {
					bucket[pos][i-1] = val;
					break;
				}
				else {
					bucket[pos][i-1] = bucket[pos][i];
				}
			}
			if(val > bucket[pos][sz-1]) {
				bucket[pos][sz-1] = val;
			}
		}
		else {
			for(int i=idx-1; i>=0; i--) {
				if(val >= bucket[pos][i]) {
					bucket[pos][i+1] = val;
					break;
				}
				else {
					bucket[pos][i+1] = bucket[pos][i];
				}
			}
			if(val < bucket[pos][0]) {
				bucket[pos][0] = val;
			}
		}
	}
}

int query(int x, int y, int k) {
	int ret = 0;
	if(ind[x] == ind[y]) {
		for(int i=x; i<=y; i++) {
			ret += (arr[i] <= k);
		}
	}
	else {
		for(int i=x; i<next[x]; i++) {
			ret += (arr[i] <= k);
		}
		for(int i=prev[y]; i<=y; i++) {
			ret += (arr[i] <= k);
		}
		for(int i=ind[x]+1; i<ind[y]; i++) {
			int num = upper_bound(bucket[i], bucket[i]+sq, k) - bucket[i];
			ret += num;
		}
	}
	return ret;
}