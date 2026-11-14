// --- LCAv3 (lowest common ancestor): ---

#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, LOG;
    vector<int> depth;
    vector<vector<int>> adj, up;

    LCA(int n) : n(n) {
        LOG = 1;
        while((1LL << LOG) <= n) ++LOG;

        adj.resize(n);
        depth.resize(n);
        up.assign(LOG, vector<int>(n));
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 0) {
        vector<int> parent(n, -1);
        queue<int> q;

        parent[root] = root;
        q.push(root);

        while(!q.empty()) {
            int v = q.front();
            q.pop();

            up[0][v] = parent[v];

            for(int c : adj[v]) {
                if(c == parent[v]) continue;

                parent[c] = v;
                depth[c] = depth[v] + 1;
                q.push(c);
            }
        }

        for(int k = 1; k < LOG; k++) {
            for(int v = 0; v < n; v++) {
                up[k][v] = up[k - 1][up[k - 1][v]];
            }
        }
    }

    int kth_ancestor(int v, int k) {
        for(int i = 0; i < LOG; i++) {
            if(k & (1LL << i))
                v = up[i][v];
        }

        return v;
    }

    int lca(int u, int v) {
        if(depth[u] < depth[v]) swap(u, v);

        // Wyrownanie glebokosci.
        u = kth_ancestor(u, depth[u] - depth[v]);

        if(u == v) return u;

        // Podnoszenie obu wierzcholkow.
        for(int k = LOG - 1; k >= 0; k--) {
            if(up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }

        return up[0][u];
    }

    int distance(int u, int v) {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    LCA tree(n);

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        --u;
        --v;

        tree.add_edge(u, v);
    }

    tree.build(0);

    int q;
    cin >> q;

    while(q--) {
        int u, v;
        cin >> u >> v;

        --u;
        --v;

        cout << tree.lca(u, v) + 1 << '\n';
    }

    return 0;
}