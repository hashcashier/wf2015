/*
1. A graph has an Eulerian circuit if and only if it is connected (once you throw out all nodes of degree 0) and every node has 'even degree'.
2. A graph has an Eulerian path if and only if it is connected and every node except two has even degree.
*/

#define MAXN 500

int adj[MAXN][MAXN];
int deg[MAXN];
vector<int> path;

void Eulerian(int u) {
    for(int v=0; v<MAXN; v++) {
        if(adj[u][v] != 0) {
            adj[u][v] --;
            adj[v][u] --;
            deg[u] --;
            deg[v] --;
            Eulerian(v);
        }
    }
    path.push_back(u);
}

void findEulerian() {
    int start;
    for(start=0; start<MAXN; start++) {
        if(deg[start] % 2 == 1) {
            break;
        }
    }
    if(start == MAXN) {
        for(start=0; start<MAXN; start++) {
            if(deg[start] != 0) {
                break;
            }
        }
    }
    Eulerian(start);
    reverse(path.begin(), path.end());
}
