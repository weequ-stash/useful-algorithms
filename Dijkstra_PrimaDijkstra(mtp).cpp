// --- Dijkstra: ---

//const int inf = INT_MAX;
//
//vector<vector<pair<int, int>>> t;
//vector<bool> vis;
//vector<int> dist;
//
//void prepare_arrays(int n) {
//    t.assign(n, {});
//    vis.assign(n, 0);
//    dist.assign(n, inf);
//}

void dijkstra(int x, int n) {
    priority_queue<pair<int, int>> pq;    //{-dist, i}

    dist[x] = 0;
    pq.push({0, x});

    while(!pq.empty()) {
        int v = pq.top().second;
        pq.pop();

        if(vis[v]) continue;
        vis[v] = 1;

        for(auto [c, c_dist] : t[v]) {
            if(dist[c] <= dist[v] + c_dist) continue;

            dist[c] = dist[v] + c_dist;
            pq.push({-1 * dist[c], c});
        }
    }
}

// --- Prima-Dijkstra (MST): ---

//const int inf = INT_MAX;
//
//vector<vector<pair<int, int>>> t;
//vector<bool> vis;
//vector<int> dist; // najtansze krawedzie
//
//void prepare_arrays(int n) {
//    t.assign(n, {});
//    vis.assign(n, 0);
//    dist.assign(n, inf);
//}

int MST(int x, int n) {
    priority_queue<pair<int, int>> pq;    // {-edge_weight, i}
    int mst_cost = 0;

    dist[x] = 0;
    pq.push({0, x});

    while(!pq.empty()) {
        int v = pq.top().second;
        int w = -pq.top().first;
        pq.pop();

        if(vis[v]) continue;
        vis[v] = 1;

        mst_cost += w;

        for(auto [c, c_dist] : t[v]) {
            if(dist[c] <= c_dist) continue;

            dist[c] = c_dist;
            pq.push({-1 * dist[c], c});
        }
    }
    return mst_cost;
}