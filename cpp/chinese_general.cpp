void merge(long long a2, long long n2, long long &a1, long long &n1) {
	long long p1, p2, r = ext_gcd(n1, n2, p1, p2), n = n1 / r * n2;
	a1 = (a1 + mulmod(mulmod((a2 - a1) / r, n1, n), p1, n)) % n, n1 = n;
}
long long chinese_remainder() {
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < i; ++j)
			if ((as[i] - as[j]) % __gcd(ns[i], ns[j]) != 0)
				return -1;
	long long n = 1, a = 0;
	for (int i = 0; i < m; ++i)
		merge(as[i], ns[i], a, n);
	if (a == 0) a += n;
	return n - a;
}