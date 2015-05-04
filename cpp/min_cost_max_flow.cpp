class MinCostMaxFlow{

  struct edge {
      int to, capcity, cost, flow;
      size_t back;
  };

  public:
  static const int MAX_N = 60 + 50;
  static const int INF = (1<<30);
  vector<edge> g[MAX_N];

  // Edges are directed!
  void addEdge(int from, int to, int cap, int cost){
    edge r1 = { to, cap, cost, 0, g[to].size() };
    edge r2 = { from, 0, -cost, 0, g[from].size() };
    g[from].push_back (r1);
    g[to].push_back (r2);
  }

  pair<int,int> max_flow(int s,int t, int k){
    int flow = 0,  cost = 0;
    while (flow < k) {
      vector<int> id (MAX_N, 0);
      vector<int> d (MAX_N, INF);
      deque<int> q;
      vector<int> p (MAX_N);
      vector<size_t> p_edge (MAX_N);
      q.push_back(s);
      d[s] = 0;
      while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        id[v] = 2;
        for (size_t i=0; i<g[v].size(); ++i) {
          edge & r = g[v][i];
          if (r.flow < r.capcity && d[v] + r.cost < d[r.to]) {
            d[r.to] = d[v] + r.cost;
            if (id[r.to] == 0)
              q.push_back(r.to);
            else if (id[r.to] == 2)
              q.push_front(r.to);
            id[r.to] = 1;
            p[r.to] = v;
            p_edge[r.to] = i;
          }
        }
      }
      if (d[t] == INF)  break;
      int addflow = k - flow;
      for (int v=t; v!=s; v=p[v]) {
        int pv = p[v];  size_t pr = p_edge[v];
        addflow = min (addflow, g[pv][pr].capcity - g[pv][pr].flow);
      }
      for (int v=t; v!=s; v=p[v]) {
        int pv = p[v];  size_t pr = p_edge[v],  r = g[pv][pr].back;
        g[pv][pr].flow += addflow;
        g[v][r].flow -= addflow;
        cost += g[pv][pr].cost * addflow;
      }
      flow += addflow;
    }
    return make_pair(flow,cost);
  }
};
