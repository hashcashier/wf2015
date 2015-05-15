point rotate_by(point &p, point &o, double rads) {
	return (p-o)*exp(point(0, rads))+o;
}
point reflect(point &p, point &about1, point &about2) {
	point z = p - about1;
	point w = about2 - about1;
	return conj(z / w) * w + about1;
}