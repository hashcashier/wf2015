/* Solves ax + by = c. If .d == 0 -> no Solutions.
   Otherwise:
            x = t.x + k * b / t.d,
            y = t.y - k * a / t.d;				*/
template<class Int> Triple<Int> ldioph(Int a,Int b,Int c){
	Triple< Int > t = egcd( a, b );
	if( c % t.d ) return Triple< Int >( 0, 0, 0 );
	t.x *= c / t.d; t.y *= c / t.d;
	return t;
}