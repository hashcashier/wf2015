LL primes[MAXP], numprimes;
bool prime[MAXP];
void sieve(bool prime[], int N){
	memset( prime, -1, N * sizeof( prime[0] ) );
	prime[0] = prime[1] = false;
//	int sqrtN = ( int )sqrt( ( double )N );
	for(LL i = 2; i <= N; i++) if(prime[i]){
		primes[numprimes++] = i;
		for(LL j=i*i;j<N;j+=i) prime[j] = false;
	}
}//O( N.log(N) )