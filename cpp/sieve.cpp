/*(simple, slow version) O( N.log(N) )*/
void sieve(bool prime[], int N){
	memset( prime, -1, N * sizeof( prime[0] ) );
	prime[0] = prime[1] = false;
	int sqrtN = ( int )sqrt( ( double )N );
	for(int i = 2; i <= sqrtN; i++) if(prime[i]){
		for( int j = i * i; j < N; j += i )
		prime[j] = false;
	}
}/*(fast, memory efficient version)
 * gP(n) is non-zero iff n is prime.
 * Requires N / 16 bytes of memory.
 * WARNING! Only works for odd numbers.*/
#define N 51000000
unsigned int prime[N / 64];
#define gP(n) (prime[n>>6]&(1<<((n>>1)&31)))
#define rP(n) (prime[n>>6]&=~(1<<((n>>1)&31)))
void sieve() {
	memset( prime, -1, sizeof( prime ) );
	unsigned int i, i2, j,
	sqrtN = (unsigned int)sqrt((double)N)+1;
	for(i = 3; i < sqrtN; i += 2 ) if(gP(i)) {
		i2 = i + i;
		for(j = i*i;j < N;j+=i2)rP(j);
	}
}