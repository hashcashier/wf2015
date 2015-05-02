/* num of +ve ints < than n relatively prime to n. */
int phi(int n){
	vector< ii > p = factor(n);
	for( int i = 0; i < ( int )p.size(); i++ )
		n /= p[i].first, n *= p[i].first - 1;
	return n;
}