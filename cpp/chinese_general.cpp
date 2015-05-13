LL posMod(LL num, LL mod) {
	return num < 0 ? ((num%mod)+mod)%mod : num%mod;
}// Complexity: O(n log(MAX(m_0, ..., m_(n-1)) )
bool succ_sub(vLL &a, vLL &m, LL &x) {
	LL a_tmp = posMod(a[0], m[0]);
	for (int i = 1; i < m.size(); ++i) {
		Triple<LL> gst = egcd<LL>(m[i-1], m[i]);
		if (abs(a_tmp - a[i]) % gst.d)
			return false;
		a_tmp = posMod(a_tmp + (a[i] - a_tmp) / gst.d * gst.x * m[i-1],
				m[i-1] / gst.d * m[i]);
	}
	x = a_tmp;
	return true;
}