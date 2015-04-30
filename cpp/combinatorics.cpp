// catalan numbers
long long C(int n) {
	return (C(n-1)*2*n*(2*n-1))/(n*(n+1));
	return NCR(2*n, n) - NCR(2*n, n+1);
	return NCR(2*n, n)/(n+1);
}
// derangements
long long D(int n) {
	return n*D(n-1) + pow(-1, n);
	return (n-1)*(D(n-1) + D(n-2));
}
// iterate over all subsets with < m elements
for (int i = 0; i < (1<<n); i=Integer.bitCount(i) < m ? i+1 : (i|(i-1))+1)
// iterate over all the subsets
for (int i=0; i < (1<<n); i++)
	// iterate over all the subsets of the i-th subset
	for(int i2 = i; i2 > 0; i2 = (i2-1) & i)