int dfsNumberCounter, dfsRoot, rootChildren;
vector<int> dfs_num, dfs_low,dfs_parent,articulation_vertex;
int V; //Number of Nodes
vector<int> adj[1000];

void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
  for (int j = 0; j < (int)adj[u].size(); j++) {
    int v = adj[u][j];
    if (dfs_num[v] == -1) {
      dfs_parent[v] = u;
      if (u == dfsRoot) rootChildren++;
      articulationPointAndBridge(v);
      if (dfs_low[v] >= dfs_num[u])
        articulation_vertex[u] = true;
      if (dfs_low[v] > dfs_num[u])
        printf(" Edge (%d, %d) is a bridge\n", u, v);
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    else if (v != dfs_parent[u])
      dfs_low[u] = min(dfs_low[u], dfs_num[v]);
  }
}

int main(){
  dfsNumberCounter = 0; dfs_num.assign(V, -1); dfs_low.assign(V, 0);
  dfs_parent.assign(V, 0); articulation_vertex.assign(V, 0);
  printf("Bridges:\n");
  for (int i = 0; i < V; i++)
    if (dfs_num[i] == -1) {
      dfsRoot = i; rootChildren = 0;
      articulationPointAndBridge(i);
      articulation_vertex[dfsRoot] = (rootChildren > 1);
    }
  printf("Articulation Points:\n");
  for (int i = 0; i < V; i++)
    if (articulation_vertex[i])
      printf(" Vertex %d\n", i);
}
