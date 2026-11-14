// --- LCA (lowest common ancestor): ---

int n, m;
const int B = 85000;

map<int, int> pr2n;
vector<int> v[B];
bool vis[B];
int e = 1;
vector<int> eur;

vector<int> T;

void fillmin(int x, int beg, int en) {
    if(beg == en)
        T[x] = eur[beg];
    else {
        int mid = (beg + en) / 2, l = 2*x, r = 2*x + 1;

        fillmin(l, beg, mid);
        fillmin(r, mid + 1, en);

        T[x] = min(T[l], T[r]);
    }
    return;
}

int minT(int x, int beg, int en, int a, int b) {
    if(a > b) return INT_MAX;

    if(a == beg && b == en)
        return T[x];

    int mid = (beg + en) / 2, l = 2*x, r = 2*x + 1;

    int lMin = minT(l, beg, mid, a, min(b, mid));
    int rMin = minT(r, mid + 1, en, max(a, mid + 1), b);

    return min(lMin, rMin);
}

void dfs(int x) {
    vis[x] = 1;

    int et = e;

    pr2n[et] = x;
    eur.push_back(et);
    e += 1;

    for(auto c : v[x]) {
        if(vis[c]) continue;

        dfs(c);
        eur.push_back(et);
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    vector<int> vtemp[n + 1];

    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        v[a].push_back(b);
        vtemp[b].push_back(a);
    }
    for(int i = 1; i <= n; i++) {
        if(vtemp[i].size() == 0) {
            dfs(i);
            break;
        }
    }

    T.resize(4 * eur.size());
    fillmin(1, 0, eur.size() - 1);

    vector<int> first(n + 1, -1);
    for(int i = 0; i < eur.size(); i++) {
        if(first[pr2n[eur[i]]] != -1) continue;

        first[pr2n[eur[i]]] = i;
    }

    int t;
    cin >> t;

    while(t--) {
        int x, y;
        cin >> x >> y;

        cout << pr2n[minT(1, 0, eur.size() - 1, min(first[x], first[y]), max(first[x], first[y]))] << '\n';
    }
    return 0;
}