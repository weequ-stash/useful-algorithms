// Napisz program znajdujący najdłuższy prefiks wzorca będący podsłowem tekstu.
//
// W pierwszym wierszu wejścia znajdują się dwie liczby m - długość wzorca oraz n - długość tekstu (m <= n <= 1000000).
// W drugim wierszu znajduje się słowo o długości m - wzorzec.
// W trzecim wierszu znajduje się słowo o długości n - tekst.

int pi[2000005];

int main() {
    int n, m;
    cin >> m >> n;

    n += m + 1;
    string s, t;

    cin >> s;
    cin >> t;

    s += '#';
    s += t;

    pi[0] = 0;

    for(int i = 1; i < n; i++) {
        int j = pi[i - 1];

        while(j > 0 && s[j] != s[i]) {
            j = pi[j - 1];
        }

        if(s[j] == s[i]) j++;

        pi[i] = j;
    }

    int maxp = -1;             //[^3^]

    for(int i = 0; i <= n; i++) {
        if(pi[i] > maxp) maxp = pi[i];
    }

    cout << maxp;

    return 0;
}

// do tego na koncu zamiast tego [^3^]:
// do obliczenia pierwszego wystapienia wzorca

for(int i = 0; i <= n; i++) {
    if(pi[i] == m) {
        cout << i - 2 * m;
        return 0;
    }
}
cout << "NIE";

// --- sama funcja pi: ---
// Napisz program obliczający funkcję Pi z algorytmu Knutha-Morrisa-Pratta.

vector<int> pi(10000);

int main() {
    int m;
    string s;

    cin >> m;
    cin >> s;

    pi[0] = 0;

    for(int i = 1; i < m; i++) {
        int j = pi[i - 1];

        while(j > 0 && s[j] != s[i]) {
            j = pi[j - 1];
        }

        if(s[j] == s[i]) j++;

        pi[i] = j;
    }

    for(int i = 0; i < m; i++) {
        cout << pi[i] << ' ';
    }

    return 0;
}