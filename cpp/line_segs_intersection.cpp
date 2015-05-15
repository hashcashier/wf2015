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
	event(){}
	event(point loc, event_type type, int r) :p(loc),t(type),ref(r){}
	bool operator<(const event &o) const {
		if(p != o.p) return cmplxCmp()(p, o.p);
		if(t != o.t) return t < o.t;
		if(ref != o.ref) return ref < o.ref;
		return sref < o.sref;
	}
};
typedef pair<line, int> idSeg;
struct sweepLineCmp {
	static double *x;
	static int A, B;
//	sweepLineCmp(double *pos):x(pos){}
	bool operator()(const idSeg &a, const idSeg &b) {
		if(a.second == A && b.second == B) return true;
		if(a.second == B && b.second == A) return false;
		if(a.second == b.second) return false;
		double dx = a.first(*x) - b.first(*x);
		return dx < 0 || (fabs(dx) < EPS && a.second < b.second);
	}
};
double *sweepLineCmp::x = nullptr;
int sweepLineCmp::A = -1;
int sweepLineCmp::B = -1;
vector<event> intersections(vector<line> &segs) {
	vector<event> res; priority_queue<event> Q;
	for(int i = 0; i < segs.size(); i++)
		Q.push(event(segs[i].p, START, i)),
		Q.push(event(segs[i].q, END, i));
	double X = 0; sweepLineCmp::x = &X;
	set<idSeg, sweepLineCmp> sweep;
	while(!Q.empty()) {
		event ev = Q.top(), neu; Q.pop();
		line tmpL = segs[0]; point tmpP;
		if(ev.t == START) {
			auto insertion = sweep.insert(idSeg(segs[ev.ref], ev.ref));
			auto it = insertion.first, r = it, s = it;
			// i am below
			if(++s != sweep.end() && intersectSS(segs[ev.ref], tmpL = s->first, tmpP))
				neu = event(tmpP, INTERS, res.size()),
				neu.ref = ev.ref, neu.sref = s->second,
				Q.push(neu), res.push_back(neu);
			// i am above
			if(it != sweep.begin() && intersectSS(segs[ev.ref], tmpL = (--r)->first, tmpP))
				neu = event(tmpP, INTERS, res.size()),
				neu.ref = r->second, neu.sref = ev.ref,
				Q.push(neu), res.push_back(neu);
		} else if(ev.t == END) {
			sweep.erase(idSeg(segs[ev.ref], ev.ref));
		} else {
			auto s = sweep.find(idSeg(segs[ev.ref], ev.ref)), t = s;
			t++;
			auto r = s, u = t;
			if(s != sweep.begin() && intersectSS(segs[t->second], segs[(--r)->second], tmpP))
				neu = event(tmpP, INTERS, res.size()),
				neu.ref = r->second, neu.sref = t->second,
				Q.push(neu), res.push_back(neu);
			if(++u != sweep.end() && intersectSS(segs[s->second], segs[u->second], tmpP))
				neu = event(tmpP, INTERS, res.size()),
				neu.ref = s->second, neu.sref = u->second,
				Q.push(neu), res.push_back(neu);
			// swap s & t
			int tid = t->second, sid = s->second;
			sweep.erase(idSeg(segs[tid], tid));
			sweep.erase(idSeg(segs[sid], sid));
			sweepLineCmp::A = tid;
			sweepLineCmp::B = sid;
			sweep.insert(idSeg(segs[tid], tid));
			sweep.insert(idSeg(segs[sid], sid));
			sweepLineCmp::A = sweepLineCmp::B = -1;
		}
		X = ev.p.real();
	}
	return res;
}