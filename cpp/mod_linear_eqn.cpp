// solves ax = b (mod n), O( log(an) + gcd( a, n ) )
template<class Int> vector<Int> msolve(Int a,Int b,Int n){
	if( n < 0 ) n = -n;
	Triple< Int > t = egcd( a, n );
	vector< Int > r;
	if( b % t.d ) return r;
	Int x = ( b / t.d * t.x ) % n;
	if( x < Int( 0 ) ) x += n;
	for( Int i = 0; i < t.d; i++ )
		r.push_back( ( x + i * n / t.d ) % n );
	return r;
}