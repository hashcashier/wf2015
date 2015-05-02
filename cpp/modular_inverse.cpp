//solves ax = 1 (mod n), O( log(an) )
template< class Int > Int inverse(Int a, Int n){
	Triple< Int > t = egcd( a, n );
	if( t.d > Int( 1 ) ) return Int( 0 );
	Int r = t.x % n;
	return( r < Int( 0 ) ? r + n : r );
}
