// Tabuleau Simplex Algorithm
#define MAXM 410
#define MAXN 410
#define EPS 1e-9
#define INF 1.0/0.0
typedef vector<double> VD;
typedef vector<int> VI;
struct smplxTable {
	vector<VD> table;
	VD solution; VI nonbasic, exit;
	double value; int m, n;
	void pivot(int E, int L) {
		double P = table[E][L];//+ve
		for(int j = 0; j <= n; j++) table[E][j] /= P;
		for(int i = 0; i <= m; i++) if(i != E) {
			P = table[i][L];
			for(int j = 0; j <= n; j++)
				table[i][j] -= P*table[E][j];
		}swap(basic[E], nonbasic[L]);
	}// Pivots on row E, Column L
	double solve() {
		
	}// Returns Maximal Goal Value
	smplxTable(vector<VD> &A, VD &B, VD &C) {
		C.push_back(0), m = B.size(), n = C.size();
		table = vector<VD>(m+2, VD(n+1, 0));
		nonbasic = VD(m+1, 0); nonbasic = VD(n, 0);
		for(int i = 0; i < m; i++)
			copy(A[i].begin(), A[i].end(), table[i].begin()),
			table[i][n+m] = B[i], nonbasic[i] = -i;
		for(int j = 0; j < n; j++) exit[j] = j;
		copy(C.begin(), C.end(), table[m].begin());
		table[m+1][n-1] = -1.0;
	} // Creates equivalent slack form
};