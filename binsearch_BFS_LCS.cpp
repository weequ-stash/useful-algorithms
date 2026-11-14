// --- BINSEARCH: ---

// vector<int> v(n);

int binsearch_lower(int x, vector<int>& v) {
    int l = 0, r = v.size();

    while(l < r) {
        int mid = l + (r - l) / 2;

        if(v[mid] >= x)
            r = mid;
        else
            l = mid + 1;
    }

    return l;
}

int binsearch_upper(int x, vector<int>& v) {
    int l = 0, r = v.size();

    while(l < r) {
        int mid = l + (r - l) / 2;

        if(v[mid] > x)
            r = mid;
        else
            l = mid + 1;
    }

    return l;
}

// --- BFS: ---

//const int inf = 1e8;
//
// vector<vector<int>> t;
// vector<bool> vis;
// vector<int> dist;
//
//void prepare_arrays(int n) {
//    t.assign(n, {});
//    vis.assign(n, 0);
//    dist.assign(n, inf);
//}

void bfs(int x, int n) {
    queue<int> q;

    q.push(x);
    dist[x] = 0;
    vis[x] = 1;

    while(!q.empty()) {
        int v = q.front();
        q.pop();

        for(auto c : t[v]) {
            if(vis[c]) continue;

            q.push(c);
            dist[c] = dist[v] + 1;
            vis[c] = 1;
        }
    }
}

// --- LCS(lowest common subsequence): ---

int LCS(string a, string b, string& s) {
    int n = a.size(), m = b.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Odtwarzanie LCS
    s = "";
    int i = n, j = m;

    while(i > 0 && j > 0) {
        if(a[i - 1] == b[j - 1]) {
            s += a[i - 1];
            i--;
            j--;
        }
        else if(dp[i - 1][j] >= dp[i][j - 1])
            i--;
        else
            j--;
    }

    reverse(s.begin(), s.end());

    return dp[n][m];
}