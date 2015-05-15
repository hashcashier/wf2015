typedef complex<double> point;
#define EPS 1e-9
double cross(point a, point b) {return imag(conj(a)*b);}
double dot(point a, point b) {return real(conj(a)*b);}
double len(point a, point b) {return dot(b-a,b-a);}
point mid(point a, point b) {return (a+b)/point(2);}
point perp(point a) {return point(-imag(a),real(a));}
point vec(point &a, point &b) {return b-a;}
enum STATE {
        IN, OUT, BOUNDARY
};
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
	double operator()(double x) const {return -(c+a*x)/b;}
};
struct circle {
	point c; double r;
	circle(point c, double r):c(c),r(r){}
	circle(point a, point b, point c) {
		point 	m1 = mid(a,b), m2 = mid(b,c),
				p1 = perp(b-a), p2 = perp(c-b);
		line 	L1(m1, p1), L2(m2, p2);
		if(intersectLL(L1, L2, this->c))
			r = len(this->c, c);
	}
	circle(point a, point b) {
		c = mid(a,b); r = len(a,b)/2;
	}
};
/** FEGLA DEFINES **/
#define sz(a) ((int)(a).size())
#define all(n) (n).begin(),(n).end()
#define EPS 1e-9
#define OO 1e9
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define polar(r,t) ((r)*exp(point(0,(t))))
#define angle(v) (atan2((v).Y,(v).X))
#define length(v) ((long double)hypot((v).Y,(v).X))
#define lengthSqr(v) (dot(v,v))
#define dot(a,b) ((conj(a)*(b)).real())
#define cross(a,b) ((conj(a)*(b)).imag())
#define rotate(v,t) (polar(v,t))
#define rotateabout(v,t,a)  (rotate(vec(a,v),t)+(a))
#define reflect(p,m) ((conj((p)/(m)))*(m))
#define normalize(p) ((p)/length(p))
#define same(a,b) (lengthSqr(vec(a,b))<EPS)
#define mid(a,b) (((a)+(b))/point(2,0))
#define perp(a) (point(-(a).Y,(a).X))
#define colliner pointOnLine