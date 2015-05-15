#define MAXN 1000

vector <pair <int, int> > var_var[MAXN];
vector <char> var_to_term[MAXN];

int seed_cnt = 0;
map <char, int> mp;

vector <string> rules;

int create_rule(string exp, int i = 0) {
	int seed1 = mp[exp[i]];
	if (exp.size() - i == 1) {
		return seed1;
	} else {
		int seed2 = create_rule(exp, i + 1);
		var_var[seed_cnt].push_back(make_pair(seed1, seed2));
		seed_cnt++;
		return seed_cnt - 1;
	}
}

void add_rule(int seed, string exp) {
	if (exp.size() == 1) {
		var_to_term[seed].push_back(exp[0]);
	} else {
		int seed1 = mp[exp[0]];
		int seed2 = create_rule(exp, 1);
		var_var[seed].push_back(make_pair(seed1, seed2));
	}
}

void chomskyNormalForm() {
	for (int r = 0; r < rules.size(); ++r) {
		if (!mp.count(rules[r][0]))
			mp[rules[r][0]] = mp.size();
		for (int i = 0; i < rules[r].size(); ++i) {
			if (rules[r][i] <= 'z' && rules[r][i] >= 'a') {
				if (!mp.count(rules[r][i])) {
					mp[rules[r][i]] = mp.size();
					int v = mp[rules[r][i]];
					var_to_term[v].push_back(rules[r][i]);
				}
			}
		}
	}
	seed_cnt = mp.size() + 1;
	for (int r = 0; r < rules.size(); ++r) {
		int seed = mp[rules[r][0]];
		string rule = rules[r].substr(6, rules[r].size() - 6);
		for (int i = 0; i < rule.size(); ++i) if (rule[i] == '|') rule[i] = ' ';
		istringstream ss(rule);
		string exp;
		while (ss >> exp) add_rule(seed, exp);
	}
}