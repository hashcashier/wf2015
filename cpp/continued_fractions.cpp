/*O( log n ) 1 + 1/x*/
void contFract(int m, int n, vector<int> &ans){
	while( n )
		ans.push_back( m / n ),
		m %= n, m ^= n ^= m ^= n; // swap(m, n)
}
