typedef complex<double> point;
double cross(point &a, point &b) {return imag(conj(a)*b);}
double dot(point &a, point &b) {return real(conj(a)*b);}
double len(point &a, point &b) {return dot(b-a,b-a);}
struct line {
	double a,b,c; point p,q;
	line(point p1, point p2):p(p1),q(p2) {
		p = p1, q = p2;
		if(fabs(p1.real() - p2.real()) < EPS)
			a = 1.0, b = 0.0, c = -p1.real();
		else
			a = p1.imag() - p2.imag(),
			b = p2.real() - p1.real(),
			c = -(a*p1.real() + b*p1.imag());
	}
};
struct circle {
	point c; double r;
	circle(point c, double r):c(c),r(r){}
};