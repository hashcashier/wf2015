double* GaussianElimination(int N, double **mat) {
  int i, j, k, L; double t;
  for (i = 0; i < N - 1; i++) {
    L = i;
    for (j = i + 1; j < N; j++)
      if (fabs(mat[j][i]) > fabs(mat[L][i]))
        L = j;
    for (k = i; k <= N; k++)
	  swap(mat[i][k], mat[L][k]);
    for (j = i + 1; j < N; j++)
      for (k = N; k >= i; k--)
        mat[j][k] -= (mat[i][k] * mat[j][i]) / mat[i][i];
  }
  double *res = new double[N];
  for (j = N - 1; j >= 0; j--) {
    for (t = 0.0, k = j + 1; k < N; k++)
	  t += mat[j][k] * res[k];
    res[j] = (mat[j][N] - t) / mat[j][j];
  }
  return res;
}
