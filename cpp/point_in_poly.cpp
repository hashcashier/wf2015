// outside 0, inside 1, on the border 2
int pt_in_poly(const vector<point> &p, const point &a) {
	int n = p.size(), inside = false;
	double Ax = real(a), Ay = imag(a);
	for (int i=0, j=n-1; i<n; j=i++) {
		double 	Ix = p[i].real(), Iy = p[i].imag(),
						Jx = p[j].real(), Jy = p[j].imag();
		point Ia = a - p[i], Ja = a - p[j];
		if (abs(cross(Ia, Ja)) < eps && dot(Ia, Ja) < eps)
			return 2;
		if ((Iy <= Ay && Ay < Jy) || (Jy <= Ay && Ay < Iy))
				if((Ax-Ix)*(Jy-Iy) < (Jx-Ix)*(Ay-Iy))
					inside = !inside;
	}
	return inside;
}