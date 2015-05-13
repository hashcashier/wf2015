typedef vector<LL> vLL;
typedef vector<vLL> vvLL;
vvLL mat_mul(vvLL &A, vvLL &B, LL mod) {
	int N=A.size(),M=A[0].size(),K=B[0].size();
	vvLL res(N, vLL(K, 0));
	for(int i = 0; i < N; i++)
		for(int j = 0; j < K; j++)
			for(int k = 0; k < M; k++)
				res[i][j] = (res[i][j]+(A[i][k]*B[k][j])%mod)%mod;
	return res;
}
vvLL mat_exp(vvLL &mat, LL pow, LL mod) {
	if(pow == 1) return mat;
	vvLL partial = mat_exp(mat, pow/2, mod);
	partial = mat_mul(partial, partial, mod);
	return pow%2 ? mat_mul(mat, partial, mod) : partial;
}
/* 0 1 0   F[n-2]   F[n-1]
 * 1 1 0 * F[n-1] = F[n]
 * 1 1 1   S[n-1]   S[n]
 */
LL fibosum(LL N, LL mod) {
	if(N < 2) return max(N, 0LL);
	vvLL mat(3, vLL(3, 0));
	mat[0][1] = 1;
	mat[1][0] = mat[1][1] = 1;
	mat[2][0] = mat[2][1] = mat[2][2]=1;
	vvLL mat_exped = mat_exp(mat, N-1, mod);
	vvLL vec(3, vLL(1, 0));
	vec[0][0] = 0; vec[1][0] = 1; vec[2][0] = 1;
	vvLL res = mat_mul(mat_exped, vec, mod);
	return res[2][0];
}
LL posMod(LL num, LL mod) {
	return num < 0 ? (num%mod)+mod : num%mod;
}