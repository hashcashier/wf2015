/* num of +ve ints < than n relatively prime to n. */
int phi(int n, vector<ii> &factors){
	for(int i = 0; i < ( int )factors.size(); i++)
		n /= factors[i].first, n *= factors[i].first-1;
	return n;
}
