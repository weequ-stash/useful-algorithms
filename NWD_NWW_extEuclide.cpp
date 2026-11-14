/*
// --- NWD: ---

int nwd(int a, int b) {
    int t;
    while(b) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Napisz program, który wczytuje trzy liczby naturalne a, b, c
// i sprawdza, czy c może być wyrażone jako liniowa kombinacja liczb
// a i b, tj. czy istnieją liczby x i y, takie, że c=ax+by.

pair<int, int> nwd_ext(int a, int b, int& nwd) {
    int x_prev = 1, y_prev = 0;
    int x = 0, y = 1;

    while(b) {
        int q = a / b;
        int temp_x = x, temp_y = y, temp_a = a;

        x = x_prev - q * x;
        y = y_prev - q * y;

        x_prev = temp_x;
        y_prev = temp_y;

        a = b;
        b = temp_a % b;
    }
    nwd = a;
    return {x_prev, y_prev};
}

bool czyjestpodzielne(int a, int b, long long c, int& x, int& y) {
    int nwd;
    pair<int, int> wsp = nwd_ext(a, b, nwd);

    if(c % nwd != 0) return false;

    x = wsp.first * (c / nwd);
    y = wsp.second * (c / nwd);

    return true;
}

// --- NWW wielu liczb: ---

void nww(map<int, long long>& num, long long b) {
    int d = 2;

    while(b != 1) {
        int cnt = 0;

        while(b % d == 0) {
            b /= d;
            cnt++;
        }

        num[d] = max(num[d], cnt);

        d++;
    }
}

int main() {
    int n;
    cin >> n;

    long long result = 1;
    map<int, long long> num;

    long long a;
    cin >> a;

    int d = 2;

    while(a != 1) {
        while(a % d == 0) {
            a /= d;
            num[d]++;
        }

        d++;
    }
    for(int i = 1; i < n; i++) {
        cin >> a;
        nww(num, a);
    }

    for(auto c : num) {
        result *= (pow(c.first, c.second));
    }

    cout << result;

    return 0;
}

*/