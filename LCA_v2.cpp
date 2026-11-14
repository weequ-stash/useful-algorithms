// --- LCA v2: ---

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n, l;
vector<vector<int>> t;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;

    for(int i = 1; i <= l; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for(auto u : t[v]) {
        if(u != p) dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if(is_ancestor(u, v))
        return u;
    if(is_ancestor(v, u))
        return v;
    for(int i = l; i >= 0; --i) {
        if(!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}

int main() {
    cin >> n;

    t.assign(n, {});

    int a_tmp, b_tmp;
    for(size_t i = 0; i < n - 1; i++) {
        cin >> a_tmp >> b_tmp;
        a_tmp--;
        b_tmp--;

        t[a_tmp].push_back(b_tmp);
        t[b_tmp].push_back(a_tmp);
    }

    preprocess(0);

    cout << lca(6, 7);

    return 0;
}