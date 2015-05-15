enum event_type {
	START, INTERS, END
};
struct cmplxCmp {
	bool operator()(const point &a, const point &b) {
		if(a.real() != b.real()) return a.real() < b.real();
		return a.imag() < b.imag();
	}
};
struct event {
	point p; int ref, sref; event_type t;
	event(point loc, event_type type, int r) :p(loc),t(type),ref(r){}
	bool operator<(const event &o) const {
		if(p != o.p)
			return cmplxCmp()(p, o.p);
		return t < o.t;
	}
};
struct sweepLineCmp {
	static double *x;
//	sweepLineCmp(double *pos):x(pos){}
	bool operator()(const line &a, const line &b) {
		return a(*x) < b(*x);
	}
};
double *sweepLineCmp::x = nullptr;

vector<event> intersections(vector<line> &segs) {
	vector<event> res;
	priority_queue<event, vector<event>> Q;
	for(int i = 0; i < segs.size(); i++)
		Q.push(event(segs[i].p, START, i)),
		Q.push(event(segs[i].q, END, i));
	double X = 0; sweepLineCmp::x = &X;
	set<line, sweepLineCmp> sweep;
	set<ii> blockedEvents;
	while(!Q.empty()) {
		event ev = Q.top(); Q.pop();
		if(ev.t == START) {
			auto insertion = sweep.insert(segs[ev.ref]);
			auto it = insertion.first, r = it, s = it;
			s++;
			if(s == sweep.end() || it == sweep.begin())
				continue;
			r--;

		} else if(ev.t == END) {

		} else if(!blockedEvents.count(ii(ev.ref,ev.sref)))
			res.push_back(ev);
	}
	return res;
}