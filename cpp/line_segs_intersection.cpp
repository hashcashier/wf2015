enum event_type {
	START, INTERS, END
};
struct cmplxCmpG {
	bool operator()(const point &a, const point &b) const {
		if(a.real() != b.real()) return a.real() > b.real();
		return a.imag() > b.imag();
	}
};
struct event {
	point p; int ref, sref; event_type t;
	event(){}
	event(point loc, event_type type, int r) :p(loc),t(type),ref(r){}
	bool operator<(const event &o) const {
		if(p != o.p) return cmplxCmpG()(p, o.p);
		if(t != o.t) return t > o.t;
		if(ref != o.ref) return ref > o.ref;
		return sref > o.sref;
	}
};
typedef pair<line, int> idSeg;

struct sweepLineCmp {
	static double *x;
	static int A, B;
	static set<ii> lessThan;
	bool operator()(const idSeg &a, const idSeg &b) {
		if(lessThan.count(ii(a.second, b.second))) return true;
		if(lessThan.count(ii(b.second, a.second))) return false;
		double dx = a.first(*x) - b.first(*x);
		return dx < -EPS || (fabs(dx) < EPS && a.second < b.second);
	}
};
double *sweepLineCmp::x = nullptr;
int sweepLineCmp::A = -1;
int sweepLineCmp::B = -1;
set<ii> sweepLineCmp::lessThan = set<ii>();
vector<event> intersections(vector<line> &segs) {
	vector<event> res; priority_queue<event> Q;
	for(int i = 0; i < segs.size(); i++)
		Q.push(event(segs[i].p, START, i)),
		Q.push(event(segs[i].q, END, i));
	double X = Q.top().p.real(); sweepLineCmp::x = &X;
	set<idSeg, sweepLineCmp> sweep; set<point, cmplxCmpG> seen;
	while(!Q.empty()) {
		event ev = Q.top(), neu; Q.pop();
		if(seen.count(ev.p)) continue;
		seen.insert(ev.p);
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
			if(fabs(X-ev.p.real()) > EPS)
				sweepLineCmp::lessThan.clear();
			sweep.erase(idSeg(segs[ev.ref], ev.ref));
		} else {
			auto s = sweep.find(idSeg(segs[ev.ref], ev.ref)), t = s;
			assert(s != sweep.end());
			t++;
			assert(t != sweep.end());
			auto r = s, u = t;
			if(s != sweep.begin() && intersectSS(segs[t->second], segs[(--r)->second], tmpP))
				if(tmpP.real() > X)
					neu = event(tmpP, INTERS, res.size()),
					neu.ref = r->second, neu.sref = t->second,
					Q.push(neu), res.push_back(neu);
			if(++u != sweep.end() && intersectSS(segs[s->second], segs[u->second], tmpP))
				if(tmpP.real() > X)
					neu = event(tmpP, INTERS, res.size()),
					neu.ref = s->second, neu.sref = u->second,
					Q.push(neu), res.push_back(neu);
			// swap s & t
			int tid = t->second, sid = s->second;
			sweep.erase(idSeg(segs[tid], tid));
			sweep.erase(idSeg(segs[sid], sid));
			sweepLineCmp::lessThan.insert(ii(tid, sid));
			sweep.insert(idSeg(segs[tid], tid));
			sweep.insert(idSeg(segs[sid], sid));
		}
		if(Q.empty() || Q.top().p.real() > ev.p.real())
			X = ev.p.real();
	}
	return res;
}