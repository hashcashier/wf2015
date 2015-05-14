// Line - Line
bool parallel(line &A, line &B) {
	point ab = A.q - A.p, cd = B.q - B.p;
	return fabs(cross(ab, cd)) < EPS;
}
bool intersectLL(line &A, line &B, point &res){
	if(parallel(A, B)) return false;
	double d1 = cross(B.p - A.p, A.q - A.p);
	double d2 = cross(B.q - A.p, A.q - A.p);
	return res = (d1 * B.q - d2 * B.p) / (d1 - d2);
}
// Line - Segment
bool intersectLS(line &A, line &B, point &res){
	intersectLL(A, B, res); double len = length(A,B);
	return length(A, res) < len && length(B, res) < len;
}
// Segment - Segment
bool intersectLS(line &A, line &B, point &res){
	return intersectLS(A, B, res) && intersectLS(B, A, res);
}
// Circle - Line
#define vec(a,b) ((b)-(a))
#define lengthSqr(v) (dot(v,v))
#define same(a,b) (lengthSqr(vec(a,b))<EPS)
int circleLineIntersection(point& p0, point& p1,
	point& cen, long double rad, point& r1, point & r2){

	if (same(p0,p1)){
		if(fabs(lengthSqr(vec(p0,cen))-(rad*rad)) < EPS) {
			r1 = r2 = p0;
			return 1;    
		}
		return 0;
	}
	long double a, b, c, t1, t2;
	a = dot(p1-p0,p1-p0);
	b = 2 * dot(p1-p0,p0-cen);
	c = dot(p0-cen,p0-cen) - rad * rad;
	double det = b * b - 4 * a * c;
	int res;
	if (fabs(det) < EPS)
		det = 0, res = 1;
	else if (det < 0)
		res = 0;
	else
		res = 2;
	det = sqrt(det);
	t1 = (-b + det) / (2 * a);
	t2 = (-b - det) / (2 * a);
	r1 = p0 + t1 * (p1 - p0);
	r2 = p0 + t2 * (p1 - p0);
	return res;
}// Circle - Segment
// Algorithm
// Algorithm
// Algorithm
// Algorithm
// Algorithm
// Circle - Circle
int CCI(point &c1, double &r1, point &c2, double &r2, point &res1, point &res2) {
	if (same(c1,c2) && fabs(r1 - r2) < EPS) {
		res1 = res2 = c1;
		return fabs(r1) < EPS ? 1 : OO;
	}
	double len = length(vec(c1,c2));
	if (fabs(len - (r1 + r2)) < EPS || fabs(fabs(r1 - r2) - len) < EPS) {
		point d, c;
		long double r;
		if (r1 > r2)
			d = vec(c1,c2), c = c1, r = r1;
		else
			d = vec(c2,c1), c = c2, r = r2;
		res1 = res2 = normalize(d) * r + c;
		return 1;
	}
	if (len > r1 + r2 || len < fabs(r1 - r2))
		return 0;
	long double a = cosRule(r2, r1, len);
	point c1c2 = normalize(vec(c1,c2)) * r1;
	res1 = rotate(c1c2,a) + c1;
	res2 = rotate(c1c2,-a) + c1;
	return 2;
}// Line - Point
point closeToLine(line &L, point &o) {
	point po = o-L.p, pq = L.q - L.p;
	double u = dot(po, pq)/length(pq);
	return L.p + u*pq;
}
// Segment - Point
point closeToSeg(line &S, point &o) {
	point po = o - S.p, pq = S.q - S.p;
	double u = dot(po, pq), vlen = length(pq);
	if(u < 0) return p;
	if(u > vlen) return q;
	return closeToLine(S, o);
}