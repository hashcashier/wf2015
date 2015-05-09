ii nim(vi &H, bool misere) {
	int X=accumulate(H.begin(), H.end(),0,bit_xor<int>());
	int L = max_element(H.begin(), H.end())-H.begin();
	if(X) for(int i=0;i<H.size();i++) if(H[i]^X<H[i]){
		int take = H[i] - (H[i]^X), more=0, ones=0;
		for(int j=0;j<H.size();j++)
			if((i!=j&&H[j]>1)||(i==j&&H[j]>take)) more++;
			else ones++;
		if(!more) {
			return ii(L, H[L] - (misere^(ones%2)));
		} return ii(i, take);
	} else if(H[L] == 1) {
		return ii(-1,0); // loss
	} return ii(L, H[L]); // or empty any other heap
}