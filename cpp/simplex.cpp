#define EPS 1e-9
typedef vector<int> VI;
typedef vector<double> VD;
struct simplex {
	vector<VD> coeff;// A|B, C|0 
	vector<bool> basic;
	double V; int m, n; VD D;
	//L: basic leaving var,E: non-basic entering var
	void pivot(int L, int E) {
		// Compute coefficients of new basic variable E
		memset(coeff[E], 0, sizeof coeff[E]);
		for(int i = 0; i < n; i++)
			if(i != E && !basic[i])
				coeff[E][i] = coeff[L][i]/coeff[L][E];
		coeff[E][L] = 1/coeff[L][E];
		// Compute remaining coefficients
		for(int i=1;i<n;i++) if(i != L && basic[i]){
			for(int j=0;j<n;j++) if(j != E && !basic[j])
				coeff[i][j] -= coeff[i][E]*coeff[E][j];
			coeff[i][L] = -coeff[i][E]*coeff[E][L];
		} // Compute Objective Function
		V += coeff[0][E]*coeff[E][0];
		for(int i = 1; i < n; i++) if(i != E && !basic[i])
			coeff[0][i] -= coeff[0][E]*coeff[E][i];
		coeff[0][L] = -coeff[0][E]*coeff[E][L];
		basic[E] = !(basic[L] = false);
	}
	VD solve() {
		// do stuff
	}
	simplex(vector<VD> &A, VD &B, VD &C){
		C.push_back(0);// <- x0, Build Slack Form
		m = B.size(), n = C.size();
		coeff = vector<VD>(2*m+1, VD(m+n+1, 0));
		basic = vector<bool>(m+n, false);
		copy(C.begin(), C.end(), coeff[2*m].begin());
		for(int i = 0; i < m; i++)
			coeff[m+i][m+n] = B[i], basic[m+i] = true;
		for(int i = 0; i < m; i++) for(int j = 0; j < n; j++)
			coeff[m+i][j] = j == n-1 ? 0 : -A[i][j];
		n += m, m <<= 1;
		// Test initial feasibility
		int k = min_element(B.begin(), B.end()) - B.begin();
		if(B[k] >= EPS) return;
		fill(coeff[2*m].begin(), coeff[2*m].end(), 0);
		for(int i = 0; i <= m; i++) coeff[m+i][n-1] = -1;
		pivot(n+k, n-1);
		VD res = solve();
		if( fabs(res[n-1]) < EPS) {
			if(basic[n-1]) {
				// do stuff
			}
		} else
			m = n = -1;
	}
};
