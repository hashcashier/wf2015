double heron(double a, double b, double c) {
	double s = (a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}
double TABH(double b, double h) {
	return b * h / 2;
}
double TA2sidesAngle(double a, double b, double t) {
	return fabs(a * b * sin(t) / 2);
}
double TA2anglesSide(double t1, double t2, double s) {
	return fabs(s * s * sin(t1) * sin(t2) / (2 * sin(t1 + t2)));
}
double TA3points(point& a, point& b, point& c) {
	return fabs(cross(a,b) + cross(b,c) + cross(c,a))/2;
}