struct sparseTable {
	vector< vector<int> > spt;
	vector<int> _arr;
	int n, lg;
	sparseTable(vector<int> &arr) {
		n = arr.size();
		for(lg = 0; (1<<lg) < n; lg++);
		spt.assign(n, vector<int>(lg));
		for(int i = 0; i < n; i++)
			_arr[i] = arr[i], spt[i][0] = i;
		for(int j = 1; (1<<j) <= n; j++)
			for(int i = 0; i +(1<<j) - 1 < n; i++)
				if( arr[spt[i][j-1]] < arr[spt[i+(1<<(j-1))][j-1]])
					spt[i][j] = spt[i][j-1];
				else
					spt[i][j] = spt[i+(1<<(j-1))][j-1]
	}
	
	int rmq(int i, int j) {
		// 2^k <= (j-i+1)
		int k = (int)floor(log((double)j-i+1) / log(2.0)), len=(1<<k);
		if(_arr[spt[i][k]] <= _arr[spt[j-len+1][k]])
			return spt[i][k];
		return spt[j-len+1][k];
	}
};