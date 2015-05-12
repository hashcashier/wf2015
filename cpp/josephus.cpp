int survive[MAXN];
void josephus(int n, int m) {
	survive[1] = 0;
	for(int i = 2; i <= n; i++)
		survive[i] = (survive[i-1]+(m%i))%i;
}