typedef vector<point> poly;
void polygonCut(poly &p, point &a, point&b, poly &res){
	res.clear(); line ab(a,b);
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		bool in1 = cross(vec(a, b), vec(a, p[i])) > EPS;
		bool in2 = cross(vec(a, b), vec(a, p[j])) > EPS;
		if (in1)
			res.push_back(p[i]);
		if (in1 ^ in2) {
			point r; line ij(p[i], p[j]);
			intersectLL(ab, ij, r);
			res.push_back(r);
		}
	}
}