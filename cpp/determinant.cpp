double determinant(vector<vd> mat) {
	int i, j, k, L, swaps=0, N = mat.size();
	for (i = 0; i < N - 1; i++) {
		L = i;
		for (j = i + 1; j < N; j++)
			if (fabs(mat[j][i]) > fabs(mat[L][i]))
				L = j;
		if(L != i) {
			swaps++;
			for (k = i; k < N; k++)
				swap(mat[i][k], mat[L][k]);
		}
		for (j=i+1; j < N; j++) for(k=N-1; k >= i; k--)
			mat[j][k]-=(mat[i][k]*mat[j][i])/mat[i][i];
	}
	double res = swaps%2 ? -1 : 1;
	for(int i = 0; i < N; i++)
		res *= mat[i][i];
	return res;
}
/* Inverse of a square matrix: First, the n by n identity matrix is augmented to the right of A, forming a n by 2n block matrix [A | I]. Now through application of elementary row operations, find the reduced echelon form of this n by 2n matrix. The matrix A is invertible if and only if the left block can be reduced to the identity matrix I; in this case the right block of the final matrix is A−1. If the algorithm is unable to reduce the left block to I, then A is not invertible. */