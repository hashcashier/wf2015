for(int i = 1; i < n-1; i++) {
	pt 	ai = pts[i] - pts[i-1],
		ib = pts[i+1] - pts[i];
	area += (conj(ai)*ib).imag();
}