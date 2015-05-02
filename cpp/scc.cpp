#include <bits/stdc++.h>
using namespace std;

#define MAXN 100

int N;
vector< vector<int> > adj;

int num[MAXN], low[MAXN];
bool vis[MAXN];
vector<int> S;
vector< vector<int> > SCCs;
int dfsNumber;

void tarjanSCC(int u) {
	low[u] = num[u] = dfsNumber ++;
	S.push_back(u);
	vis[u] = 1;
	for(int i=0; i<adj[u].size(); i++) {
		int v = adj[u][i];
		if(num[v] == -1)
			tarjanSCC(v);
		if(vis[v] == 1)
			low[u] = min(low[u], low[v]);
	}
	if(low[u] == num[u]) {
		vector<int> SCC;
		while(1) {
			int v = S.back();
			S.pop_back();
			vis[v] = 0;
			SCC.push_back(v);
			if(u == v)
				break;
		}
		SCCs.push_back(SCC);
	}
}

void findSCC() {
  dfsNumber = 0;
	memset(vis, 0, sizeof(vis));
	memset(num, -1, sizeof(num));
	memset(low, 0, sizeof(low));
	S.clear();
	SCCs.clear();
	for(int i=0; i<N; i++)
		if(num[i] == -1)
			tarjanSCC(i);
}
