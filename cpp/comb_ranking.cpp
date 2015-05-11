long long rank_comb(int n, vi c) {
	long long res = 0, prev = - 1, k = c.size();
	sort(c.begin(), c.end());
	for(int i = 0; i < c.size(); i++)
		res += RCN_S(n-prev-2,k-i-1)-RCN_S(n-c[i]-1,k-i-1),
		prev = c[i];
	return res;
}
struct comp{
	long long b;
	comp(long long base):b(base){}
	int operator ()(const LL &a, const LL &val) {
		return (b-a)>val;
	}
};
// requires NCR with rcn[k][n] matrix + row sum rcn_s
vi unrank_comb(int n, int k, int r) {
	vi res;
	for(int i=k-1,j=-1; i >= 0; i--) {
		LL b = rcn_s[i][n-j-2];
		j = n-1-(lower_bound(rcn_s[i], rcn_s[i]+n-j-1, r, comp(b))-rcn_s[i]),
		r -= b-rcn_s[i][n-j-1],
		res.push_back(j);
	} return res;
}