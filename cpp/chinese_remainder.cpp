// returns minimum X satisfying X = Ai mod Ni for all i
int chinese_remainder(int *n, int *a, int len){
	int p, i, prod = 1, sum = 0;
	for (i = 0; i < len; i++) prod *= n[i];
	for (i = 0; i < len; i++)
		p = prod / n[i],
		sum += a[i] * inverse(p, n[i]) * p;
	return sum % prod;
}