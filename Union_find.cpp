vector<int> rep;
vector<int> vsize;
int scc;           // liczba spojnych skladowych grafu

int uFind(int x) {
    if(rep[x] != x) {
        rep[x] = uFind(rep[x]);
    }
    return rep[x];
}

void uNion(int a, int b) {
    a = uFind(a);
    b = uFind(b);

    if(a == b) return;

    if(vsize[a] > vsize[b]) swap(a, b);

    rep[a] = b;
    vsize[b] += vsize[a];
    scc--;
}

void prepare_arrays(int n) {
    rep.assign(n, 0);
    vsize.assign(n, 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    scc = n;

    for(int i = 0; i < n; i++) {
        rep[i] = i;
    }

    for(int i = 0; i < m; i++) {
        int g, h;
        cin >> g >> h;

        g--;
        h--;

        uNion(g, h);

        cout << scc << '\n';
    }
    return 0;
}