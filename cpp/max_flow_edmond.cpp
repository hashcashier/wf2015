class MaxFlow{

  struct edge {
      int to, capcity, flow;
      size_t back;
  };

  public:
  static const int MAX_N = 60 + 50;
  static const int INF = (1<<30);
  vector<edge> g[MAX_N];

  // Edges are directed!
  void addEdge(int from, int to, int cap){
    edge r1 = { to, cap, 0, g[to].size() };
    edge r2 = { from, 0, 0, g[from].size() };
    g[from].push_back (r1);
    g[to].push_back (r2);
  }

  int max_flow(int s,int t){
    int flow = 0;
    while (true) {
      queue<int> q;
      vector<int> p (MAX_N);
      vector<int> d(MAX_N, INF);
      vector<size_t> p_edge (MAX_N);
      q.push(s);
      d[s] = 0;
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        if(v == t) break;
        for (size_t i=0; i<g[v].size(); ++i) {
          edge & r = g[v][i];
          if (r.flow < r.capcity && d[v]+1 < d[r.to]) {
            q.push(r.to);
            p[r.to] = v;
            p_edge[r.to] = i;
            d[r.to] = d[v] + 1;
          }
        }
      }
      if(d[t] == INF) break;
      int addflow = (1<<30);
      for (int v=t; v!=s; v=p[v]) {
        int pv = p[v];  size_t pr = p_edge[v];
        addflow = min (addflow, g[pv][pr].capcity - g[pv][pr].flow);
      }
      for (int v=t; v!=s; v=p[v]) {
        int pv = p[v];  size_t pr = p_edge[v],  r = g[pv][pr].back;
        g[pv][pr].flow += addflow;
        g[v][r].flow -= addflow;
      }
      flow += addflow;
    }
    return flow;
  }
};
