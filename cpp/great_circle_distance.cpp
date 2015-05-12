// Returns great circle distance (lat[90,90],long[180,180])
double greatcircle(double lt1, double lo1, double lt2, double lo2, double r) {
	double a = M_PI*(lt1/180.0), b = M_PI*(lt2/180.0);
	double c = M_PI*((lo2lo1)/180.0);
	return r*acos(sin(a)*sin(b) + cos(a)*cos(b)*cos(c));
}