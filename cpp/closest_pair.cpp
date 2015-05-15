typedef pair<double, int> di;
ii closestPair(vector<point> &pts) {
	if(pts.size() < 2) return ii(-1, -1);
	set<di> window, active;
	double d = len(pts[0], pts[1]);
	ii res = ii(0, 1);
	window.insert(di(real(pts[0]), 0));
	window.insert(di(real(pts[1]), 1));
	active.insert(di(imag(pts[0]), 0));
	active.insert(di(imag(pts[1]), 1));
	for(int i = 2; i < pts.size(); i++) {
		for(auto it = window.begin(); it != window.end(); it = window.begin())
			if(pts[i].real() - it->first > d)
				active.erase(di(imag(pts[it->second]),it->second)),
				window.erase(it);
			else break;
		for(auto it = active.lower_bound(di(imag(pts[i])-d, 0)); it != active.end(); it++)
			if(it->first - imag(pts[i]) < d)
				d = min(d, len(pts[i], pts[it->second]));
			else break;

		window.insert(di(real(pts[i]), i));
		active.insert(di(imag(pts[i]), i));
	}
	return res;
}