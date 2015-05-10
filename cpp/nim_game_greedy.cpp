ii nimGreedy(VI &H) {
	int m = 0, n = 0, pm = 0, pn = 0, mi = -1;
	for(int i = 0; i < H.size(); i++)
		if(H[i] > m) n=m, pn=pm, m=H[i], pm=1, mi=i;
		else if(m > H[i] && H[i] > n) n = H[i], pn = 1;
		else if(H[i] == m) pm++;
		else if(H[i] == n) pn++;
	if(pm%2 == 0) return ii(mi,0);
	else if(pm == 1) return ii(mi, pn%2 ? m-n : m);
	return ii(mi,m);//[1..m],[m-n+1 .. m]
}