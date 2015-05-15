void voronoi(poly &pnts, poly& rect, vector<poly> &res){
	res.clear();
	for (int i = 0; i < pnts.size(); i++) {
		res.push_back(rect);
		for (int j = 0; j < pnts.size(); j++) {
			if (j == i)
				continue;
			point 	p = perp(vec(pnts[i], pnts[j])),
					m = mid(pnts[i], pnts[j]), mp = m+p;
			vector<point> temp;
			polygonCut(res.back(), m, mp, temp);
			res.back() = temp;
		}
	}
}