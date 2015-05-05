int primes[100000];
bool prime[100000];
void sieve(bool prime[], int N){
	memset( prime, -1, N * sizeof( prime[0] ) );
	prime[0] = prime[1] = false;
	int sqrtN = ( int )sqrt( ( double )N );
	for(int i = 2, j = 0; i <= sqrtN; i++) if(prime[i]){
		primes[j++] = i;
		for(int j = i * i;j < N;j += i) prime[j] = false;
	}
}//O( N.log(N) )