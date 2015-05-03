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
// Algorithm
// Algorithm
// Algorithm
// Algorithm
// Algorithm
// Circle - Segment
// Algorithm
// Algorithm
// Algorithm
// Algorithm
// Algorithm
// Circle - Circle
// Algorithm
// Algorithm
// Algorithm
// Algorithm
// Algorithm
// Line - Point
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