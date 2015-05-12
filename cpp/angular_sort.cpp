bool sameSlope(pt &a, pt &b) {
    return a.imag()*b.real() == b.imag()*a.real();
}
bool slopeLess(pt &a, pt &b) {
    return a.imag()*b.real() < b.imag()*a.real();
}
struct quadSort {
    int wrt;
    quadSort(int WRT) {
        wrt = WRT;
    }
    int quad(const pt &p) const {
        if(p.imag() < 0)
            return 3 - (p.real() < 0);
        return p.real() < 0;
    }
    bool operator()(const int &a, const int &b) const {
        pt A = pts[a] - pts[wrt], B = pts[b] - pts[wrt];
        int qa = quad(A), qb = quad(B);
		if(qa != qb) return qa < qb;
        if(!sameSlope(A, B) return slopeLess(A, B);
		return norm(A) < norm(B);
    }
};