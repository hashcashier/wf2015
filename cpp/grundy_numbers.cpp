int g(int u) { // no standard or general way to do it
	/* minimal excludant:
	   smallest non-negative number not found
	   amongst followers/neighbors of u */
	return mex(F(u));
} // for sum of games, xor all SG-values (nim)