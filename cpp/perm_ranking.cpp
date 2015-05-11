void rec_unrank_perm(int n, int k, LL r, vi &id, vi &pi) {
	if(k) {
		swap(id[n - 1], id[r % n]);
		rec_unrank_perm(n - 1, k - 1, r / n, id, pi);
		pi.push_back(id[n - 1]);
		swap(id[n - 1], id[r % n]);
	}
}
// Returns a kpermutation corresponds to rank 'r' of n objects.
// 'id' should be a full identity permutation of size at least n
// and it remains the same at the end of the function
vi unrank_perm(int n, int k, LL r, vi &id) {
	vi ans;
	rec_unrank_perm(n, k, r, id, ans);
	return ans;
}
LL rec_rank_perm(int n, int k, vi &pirev, vi &pi){
	if (!k)	return 0;
	int s = pi[k-1];
	swap(pi[k-1], pi[ pirev[n-1]-(n-k) ]);
	swap(pirev[s], pirev[n-1]);
	LL ans = s + n * rec_rank_perm(n-1, k-1, pirev, pi);
	swap(pirev[s], pirev[n-1]);
	swap(pi[k-1], pi[pirev[n-1]-(n-k)]);
	return ans;
}
// Returns rank of the kpermutaion 'pi' of n objects.
// 'id' should be a full identity permutation of size at least n
// and it remains the same at the end of the function
LL rank_perm(int n, vector<int> &id, vector<int> pi) {
	for(int i=0;i<pi.size();i++)
		id[pi[i]] = i+n-pi.size();
	LL ans = rec_rank_perm(n, pi.size(), id, pi);
	for(int i=0;i<pi.size();i++)
		id[pi[i]] = pi[i];
	return ans;
}