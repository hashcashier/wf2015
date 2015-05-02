// The number of primitive roots modulo n,
// if there are any, is equal to phi( phi(n) )
bool is_primitive_root(int g, int n) {
	vector<int> phiF = factor(phi(n));
	for(int i = 0; i < phiF.size(); i++)
		if(fastpow(g,(phiF.size()-1)/phiF[i].first)%n == 1)
			return false;
	return true;
}// finds x -> g^x = a mod n
int baby_giant_disc(int g, int a, int n){
	int m = ceil(sqrt(n));
	map<int, int> table; // can use hashing here
	for(LL gi = 1, i = 0; i < m; i++, gi = (gi*g)%n)
		if(!table.count(gi))
			table[gi] = i;
	for(LL i=0,y=a,q=inverse(pow(g, m)%n, n); i < m; i++){
		if(table.count(y))
			return i*m + table[y];
		else
			y = (y*q)%n;
	}
	return -1; // error.. invalid input
}