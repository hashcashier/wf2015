vii factor(LL N) {
	vii res;
	for(int i=0,j=0; primes[i]*primes[i] <= N; i++,j=0){
		while(N % primes[i] == 0) j++, N /= primes[i];
		if(j) res.push_back(ii(primes[i],j));
	} if(N > 1) res.push_back(ii(N,1));
	return res;
}