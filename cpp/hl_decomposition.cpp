// Should also built subsize array which is the size of the subtree of a node
// including itself and a parent array which stores the parent of each node.
int chainNo=0,chainHead[N],chainPos[N],chainInd[N],chainSize[N];
memset(chainHead,-1,sizeof chainHead);
void hld(int cur) {
  if(chainHead[chainNo] == -1) chainHead[chainNo]=cur;
  chainInd[cur] = chainNo;
  chainPos[cur] = chainSize[chainNo];
  chainSize[chainNo]++;

  int ind = -1,mai = -1;
  for(int i = 0; i < (int)adj[cur].size(); i++) {
    if(adj[cur][i] != parent[cur] && subsize[ adj[cur][i] ] > mai) {
      mai = subsize[ adj[cur][i] ];
      ind = i;
    }
  }

  if(ind >= 0) hld( adj[cur][ind] );

  for(int i = 0; i < (int)adj[cur].size(); i++) {
    if(adj[cur][i] != parent[cur] && i != ind) {
      chainNo++;
      hld( adj[cur][i] );
    }
  }
}

// You will need also an array containing the depth of each node
int LCA(int u,int v){
  int curru=u, currv=v;
  while(true){
    if( chainInd[curru] == chainInd[currv] ){
      if( chainPos[curru] > chainPos[currv] )
        return currv;
      else
        return curru;
    }
    if( depth[chainHead[chainInd[curru]]] > depth[chainHead[chainInd[currv]]] ){
      curru = chainHead[chainInd[curru]];
      if(parent[curru] != -1) curru = parent[curru];
    }else{
      currv = chainHead[chainInd[currv]];
      if(parent[currv] != -1) currv = parent[currv];
    }
  }
  return -1;
}

