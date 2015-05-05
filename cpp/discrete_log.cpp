// logairthmic modular power
long long fastpow(long long N, long long p, long long mod) {
	if(p == 1)
		return N%mod;
	long long subres = fastpow(N, p/2, mod);
	if(p%2)	return (((N*subres)%mod)*subres)%mod;
	return (subres*subres)%mod;
}// The number of primitive roots modulo n,
// if there are any, is equal to phi( phi(n) )
bool is_primitive_root(int g,int n,int pN,vector<ii> &pF){
//	vector<ii> pF = factor(phi(n));
	for(int i = 0; i < pF.size(); i++)
		if(fastpow(g,pN/pF[i].first, n)==1)	return false;
	return true;
}// finds x -> g^x = a mod n
int baby_giant_disc(int g, int a, int n){
	int m = ceil(sqrt(n)); map<int, int> table; // can use hashing here
	for(LL gi = 1, i = 0; i < m; i++, gi = (gi*g)%n)
		if(!table.count(gi))
			table[gi] = i;
	for(LL i=0,y=a,q=inverse<long long>(fastpow(g, m, n), n); i < m; i++)
		if(table.count(y)) return i*m + table[y];
		else y = (y*q)%n;
	return -1; // error.. invalid input
}// returns smallest primitive root of a number
int smallest_primitive(int n) {
	vector<ii> nfactors = factor(n);
	int phiN = phi(n, nfactors);
	vector<ii> phiF = factor(phiN);
	for(int i=2,k=1; i < n; i++,k=1) {
		for(int j = 0; k && j < nfactors.size(); j++)
			if(i%nfactors[j].first == 0) k=0;
		if(k && is_primitive_root(i, n, phiN, phiF))
			return i;
	} return -1; // no primitive roots
}// add primitive root rules