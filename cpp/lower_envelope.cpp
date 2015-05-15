/*
Solves y=mx+b; dp[i] = {Min: 0 < j < i} f[j]*g[i] + dp[j]
Queries:
1. Incrementally; dp[i] from i=0..N. Use 'query' in code.
2. Arbitrary. Use binary search.
Insertions:
1. Offline. All lines are inserted before queries. Sort them in desc order by slope then use 'add' in code.
2. Online. Lines are inserted in lower order. Use 'add' in code.
3. Online. Lines are inserted in higher order. Use 'dequeue'.
4. Online. Lines are inserted in arbitrary order. Use 'set' for 'add' and 'set' for 'query'.
*/

#define MAXN 1000

int N;

int dp[MAXN];
vector<long long> M, B;
int pointer;

bool isBad(int line1, int line2, int line3) {
	return (B[line3]-B[line1])*(M[line1]-M[line2]) < (B[line2]-B[line1])*(M[line1]-M[line3]);
}

void add(long long m, long long b) {
	M.push_back(m);
	B.push_back(b);
	while(M.size() >= 2 && isBad(M.size()-3, M.size()-2, M.size()-1) == true) {
		M.erase(M.end()-2);
		B.erase(B.end()-2);
	}
}

long long query(long long x) {
	if(pointer >= M.size()) {
		pointer = M.size() - 1;
	}
	//This gets lower envelope. For upper envelope, use 'greater than'
	while(pointer < M.size()-1 && M[pointer+1]*x+B[pointer+1] < M[pointer]*x+B[pointer]) {
		pointer ++;
	}
	return M[pointer]*x+B[pointer];
}

void solve() {
	for(int i=0; i<N; i++) {
		dp[i] = query(g[i]); //dp[i] = f[pointer]*g[i] + dp[pointer]
		add(f[i], dp[i]); //m = f[i], b = dp[i]
	}
}