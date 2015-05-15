/*
1. Set get_val function accordingly
2. Terminals have values from a to z (0..25)
3. Epsilon has value of 26
4. last_var starts from 27
*/

#define MAXN 1000

vector<int> dp[MAXN][MAXN];

int last_var;
vector< vector<int> > grammar[MAXN];
int start, N;

int getVal(char c) {
	return c - 'a';
}

bool isValid(int var, vector<int> rule) {
	for(int i=0; i<grammar[var].size(); i++) {
		if(grammar[var][i].size() == rule.size()) {
			int j = 0;
			for(int j=0; j<rule.size(); j++) {
				if(rule[j] != grammar[var][i][j]) {
					break;
				}
			}
			if(j == rule.size()) {
				return true;
			}
		}
	}
	return false;
}

vector<int> getVars(vector<int> rule) {
	vector<int> ret;
	for(int i=27; i<last_var; i++) {
		if(isValid(i, rule) == true) {
			ret.push_back(i);
		}
	}
	return ret;
}

bool CYK(string word) {
	vector<int> ret, rule;
	rule.assign(1, 26);
	if(word == "" && isValid(start, rule) == true) {
		return true;
	}
	for(int i=0; i<word.size(); i++) {
		rule.assign(1, getVal(word[i]));
		ret = getVars(rule);
		for(int j=0; j<ret.size(); j++) {
			dp[i][i].push_back(ret[j]);
		}
	}
	for(int len=2; len<=N; len++) {
		for(int i=0; i<N-len+1; i++) {
			int j = i + len - 1;
			for(int k=i; k<j; k++) {
				for(int p=0; p<dp[i][k].size(); p++) {
					for(int q=0; q<dp[k+1][j].size(); q++) {
						rule.clear();
						rule.push_back(dp[i][k][p]);
						rule.push_back(dp[k+1][j][q]);
						ret = getVars(rule);
						for(int r=0; r<ret.size(); r++) {
							dp[i][j].push_back(ret[r]);
						}
					}
				}
			}
		}
	}
	vector<int> chk = dp[0][N-1];
	for(int i=0; i<chk.size(); i++) {
		if(chk[i] == start) {
			return true;
		}
	}
	return false;
}