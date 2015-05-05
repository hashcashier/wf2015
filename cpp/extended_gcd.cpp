typedef pair<int, int> ii;
typedef long long LL;
typedef vector<ii> vii;
LL gcd( LL a, LL b )
{ return( b == 0 ? a : gcd( b, a % b ) ); }
//USED BY: egcd, msolve, inverse, ldioph
template<class Int> struct Triple{
	Int d, x, y;
	Triple(Int q, Int w, Int e):d(q), x(w), y(e){}
};//USED BY: msolve, inverse, ldioph
template<class Int> Triple<Int> egcd(Int a, Int b){
	if(!b) return Triple<Int>(a, Int( 1 ), Int( 0 ));
	Triple<Int> q = egcd( b, a % b );
	return Triple<Int>( q.d, q.y, q.x - a / b * q.y );
}