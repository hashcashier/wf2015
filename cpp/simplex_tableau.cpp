// Tabuleau Simplex Algorithm
#define MAXM 410
#define MAXN 410
#define EPS 1e-11
#define INF 1.0/0.0
typedef vector<double> VD;
typedef vector<int> VI;
struct smplxTable {
	vector<VD> T;
	VD X; VI nonbasic, basic;
	int m, n;
	void pivot(int E, int L) {
		double P = T[E][L];//+ve
		for(int j = 0; j <= n; j++) T[E][j] /= P;
		for(int i = 0; i <= m; i++) if(i != E) {
			P = T[i][L];
			for(int j = 0; j <= n; j++)
				T[i][j] -= P*T[E][j];
		}swap(basic[E], nonbasic[L]);
	}// ^ Pivots on row E, Column L
	double solve() {
		for(int mi=0,mj=0;;mi=mj=0) {
			for(int i=1;i<m;i++)
				if(T[i][n]<T[mi][n]) mi = i;
			if(T[mi][n] > -EPS) break;
			for(int j=1;j<n;j++)
				if(T[mi][j]<T[mi][mj]) mj = j;
			if(T[mi][mj] >= -EPS) return -INF;
			pivot(mi,mj);
		} // ^ Initial BF Solution
		for(int mi=0,mj=0;;mi=mj=0) {
			for(int j=1;j<n;j++) {
				double diff = T[m][mj]-T[m][j];
				if(diff > 0 || (fabs(diff) < EPS && nonbasic[j] < nonbasic[mj]))
					mj = j;
			}
			if(T[m][mj] > -EPS) break;
			for(int i=1;i<m;i++) if(T[i][mj]>0) {
				double diff = T[mi][n]/T[mi][mj]-T[i][n]/T[i][mj];
				if(T[i][mj] <= EPS) continue;
				if(diff > EPS || (fabs(diff) < EPS && basic[i] < basic[mi]))
					mi=i;
			}
			if(T[mi][mj] <= EPS) return INF;
			pivot(mi, mj);
		}
		X = VD(n, 0);
		for(int i = 0; i < m; i++)
			if(basic[i] >= 0) X[basic[i]] = T[i][n];
		return T[m][n];
	}// ^ Returns Maximal Goal Value
	smplxTable(vector<VD> &A, VD &B, VD &C) {
		C.push_back(0), m = B.size(), n = C.size()+1;
		T = vector<VD>(m+1, VD(n+1, 0));
		basic = VI(m+1, 0); nonbasic = VI(n, 0);
		for(int i = 0; i < m; i++)
			copy(A[i].begin(), A[i].end(), T[i].begin()),
			T[i][n] = B[i], basic[i] = -i-1;
		for(int j = 0; j < n; j++)
			nonbasic[j] = j, T[m][j] = -C[j];
	} // ^Creates equivalent slack form
};