// 2X Area Calculation, expects point pts[]
double twiceArea() { // REFERENCE IS ORIGIN
	double res = 0;
	for(int i = 0, j = 1; i < n; ++i, j = (i+1)%n)
		res += cross(pts[i],pts[j]);
	return res;
}// Centroid (Uniform-Material Center of mass)
point com() {
	point C(0,0);
	for(int i=0,j=1,cP; i < n; i++, j = (i+1)%n)
		cP = cross(pts[i], pts[j]),
		C += cP*pt(	pts[i].real() + pts[j].real(),
					pts[i].imag() + pts[j].imag());
	return C / (3*twiceArea());
}
