// logairthmic modular power
LL fastpow(LL N, LL p, LL mod) {
	if(p == 1) return N%mod;
	LL subres = fastpow(N, p/2, mod);
	if(p%2)	return (((N*subres)%mod)*subres)%mod;
	return (subres*subres)%mod;
}// The number of primitive roots modulo n,
// if there are any, is equal to phi( phi(n) )
bool is_primitive_root(int g,int n,int pV,vii &pF){
	for(int i = 0; i < pF.size(); i++)
		if(fastpow(g,pV/pF[i].first, n) == 1)
			return false;
	return true;
}// finds x -> g^x = a mod n
int baby_giant_disc(int g, int a, int n){
	int m = ceil(sqrt(n));
	map<int, int> table; // can use hashing here
	for(LL gi = 1, i = 0; i < m; i++, gi = (gi*g)%n)
		if(!table.count(gi)) table[gi] = i;
	for(LL i=0,y=a,q=inverse<LL>(fastpow(g,m,n),n);i<m;i++){
		if(table.count(y)) return i*m + table[y];
		else y = (y*q)%n;
	}
	return -1; // error.. invalid input
}// returns smallest primitive root of a number
int smallest_primitive(int n, vii &nF, int pN, vii& pF){
	for(int i=2,k=1; i < n; i++,k=1) {
		for(int j = 0; k && j < nF.size(); j++)
			if(i%nF[j].first == 0) k=0;
		if(k && is_primitive_root(i, n, pN, pF))
			return i;
	} return -1; // no primitive roots
}// solves x^k = a (mod n)
vector<int> disc_roots(int n, int k, int a) {
	vector<int> res;
	vector<ii> nF = factor(n);
	int phiN = phi(n, nF);
	vector<ii> phiFactors = factor(phiN);

	int	g = smallest_primitive(n, nF, phiN, phiFactors);
	int	y = baby_giant_disc(fastpow(g,k,n), a, n);
	if(g == -1 || y == -1) return res;
	int d = phiN / gcd(k, phiN);
	for(int i = y%d; i < phiN; i += d)
		res.push_back(fastpow(g, i, n));
	return res;
}