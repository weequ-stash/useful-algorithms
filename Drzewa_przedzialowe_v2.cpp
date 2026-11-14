//#include <bits/stdc++.h>
//using namespace std;

// Range Add + Range Query (max)

struct SegmentTree_RangeRange {
    int n;
    vector<long long> T, L;

    SegmentTree_RangeRange(int n) : n(n) {
        T.assign(4 * n, 0);
        L.assign(4 * n, 0);
    }

    void Propagate(int x, int beg, int en) {
        if(L[x] == 0 || beg == en) return;

        int mid = (beg + en) / 2;
        int l = 2 * x, r = 2 * x + 1;

        T[l] += L[x];
        T[r] += L[x];

        L[l] += L[x];
        L[r] += L[x];

        L[x] = 0;
    }

    void Add_impl(int x, int beg, int en, int a, int b, long long val) {
        if(b < beg || a > en) return;

        if(a <= beg && en <= b) {
            T[x] += val;
            L[x] += val;
            return;
        }

        Propagate(x, beg, en);

        int mid = (beg + en) / 2;

        Add_impl(2*x, beg, mid, a, b, val);
        Add_impl(2*x+1, mid+1, en, a, b, val);

        T[x] = max(T[2*x], T[2*x+1]);
    }

    long long MaxVal_impl(int x, int beg, int en, int a, int b) {
        if(b < beg || a > en) return LLONG_MIN;

        if(a <= beg && en <= b) return T[x];

        Propagate(x, beg, en);

        int mid = (beg + en) / 2;

        return max(MaxVal_impl(2*x, beg, mid, a, b), MaxVal_impl(2*x+1, mid+1, en, a, b));
    }

    void Add(int a, int b, long long val) {
        if(a <= b) Add_impl(1, 0, n-1, a, b, val);
    }

    long long MaxVal(int a, int b) {
        if(a > b) return LLONG_MIN;

        return MaxVal_impl(1, 0, n-1, a, b);
    }
};

/* przyklad

int main() {
    SegmentTree_RangeRange st(100001);

    st.Add(5, 10, 7);
    st.Add(8, 12, 3);

    cout << st.MaxVal(5, 12);
    return 0;
}

*/

// Range Add + Point Query (value)

struct SegmentTree_RangePoint {
    int n;
    vector<long long> T;

    SegmentTree_RangePoint(int n) : n(n) {
        T.assign(4 * n, 0);
    }

    void Add_impl(int x, int beg, int en, int a, int b, long long val) {
        if(b < beg || a > en) return;

        if(a <= beg && en <= b) {
            T[x] += val;
            return;
        }

        int mid = (beg + en) / 2;

        Add_impl(2*x, beg, mid, a, b, val);
        Add_impl(2*x+1, mid+1, en, a, b, val);
    }

    long long Val_impl(int x, int beg, int en, int pos) {
        if(beg == en) return T[x];

        int mid = (beg + en) / 2;

        if(pos <= mid)
            return T[x] + Val_impl(2*x, beg, mid, pos);
        else
            return T[x] + Val_impl(2*x+1, mid+1, en, pos);
    }

    void Add(int a, int b, long long val) {
        if(a <= b) Add_impl(1, 0, n-1, a, b, val);
    }

    long long Val(int pos) {
        return Val_impl(1, 0, n-1, pos);
    }
};

/* przyklad

int main() {
    SegmentTree_RangePoint st(100001);

    st.Add(5, 10, 7);
    st.Add(8, 12, 3);

    cout << st.Val(5);
    return 0;
}

*/

// Point Assignment + Range Query (sum)

struct SegmentTree_PointRange {
    int n;
    vector<long long> T;

    SegmentTree_PointRange(int n) : n(n) {
        T.assign(4 * n, 0);
    }

    void Build_impl(int x, int beg, int en, const vector<long long>& arr) {
        if(beg == en) {
            T[x] = arr[beg];
            return;
        }

        int mid = (beg + en) / 2;

        Build_impl(2*x, beg, mid, arr);
        Build_impl(2*x+1, mid+1, en, arr);

        T[x] = T[2*x] + T[2*x+1];
    }

    void Change_impl(int x, int beg, int en, int pos, long long val) {
        if(beg == en) {
            T[x] = val;
            return;
        }

        int mid = (beg + en) / 2;

        if(pos <= mid)
            Change_impl(2*x, beg, mid, pos, val);
        else
            Change_impl(2*x+1, mid+1, en, pos, val);

        T[x] = T[2*x] + T[2*x+1];
    }

    long long Sum_impl(int x, int beg, int en, int a, int b) {
        if(b < beg || a > en) return 0;

        if(a <= beg && en <= b) return T[x];

        int mid = (beg + en) / 2;

        return Sum_impl(2*x, beg, mid, a, b) + Sum_impl(2*x+1, mid+1, en, a, b);
    }

    void Build(const vector<long long>& arr) { // jezeli sa wartosci poczatkowe
        Build_impl(1, 0, n-1, arr);
    }

    void Change(int pos, long long val) {
        Change_impl(1, 0, n-1, pos, val);
    }

    long long Sum(int a, int b) {
        return Sum_impl(1, 0, n-1, a, b);
    }
};

/* przyklad

int main() {
    SegmentTree_PointRange st(100001);

    st.Change(5, 12);
    st.Change(8, 12);

    cout << st.Sum(4, 8);
    return 0;
}

*/

// Range Add + Range Query (min + sum)

struct SegmentTree_ProMax {
    int n;

    vector<long long> Tsum, Tmin, L;

    SegmentTree_ProMax(const vector<long long>& arr) {
        n = arr.size();

        Tsum.assign(4 * n, 0);
        Tmin.assign(4 * n, 0);
        L.assign(4 * n, 0);

        Build(1, 0, n-1, arr);
    }

    void Build(int x, int beg, int en, const vector<long long>& arr) {
        if(beg == en) {
            Tsum[x] = Tmin[x] = arr[beg];
            return;
        }

        int mid = (beg + en) / 2;

        Build(2*x, beg, mid, arr);
        Build(2*x+1, mid+1, en, arr);

        Tsum[x] = Tsum[2*x] + Tsum[2*x+1];
        Tmin[x] = min(Tmin[2*x], Tmin[2*x+1]);
    }

    void Propagate(int x, int beg, int en) {
        if(L[x] == 0 || beg == en) return;

        int mid = (beg + en) / 2;
        int l = 2*x, r = 2*x+1;

        long long val = L[x];

        // Lewe dziecko
        Tsum[l] += val * (mid - beg + 1);
        Tmin[l] += val;
        L[l] += val;

        // Prawe dziecko
        Tsum[r] += val * (en - mid);
        Tmin[r] += val;
        L[r] += val;

        L[x] = 0;
    }

    void Add_impl(int x, int beg, int en, int a, int b, long long val) {
        if(b < beg || a > en) return;

        if(a <= beg && en <= b) {
            Tsum[x] += val * (en - beg + 1);
            Tmin[x] += val;
            L[x] += val;
            return;
        }

        Propagate(x, beg, en);

        int mid = (beg + en) / 2;

        Add_impl(2*x, beg, mid, a, b, val);
        Add_impl(2*x+1, mid+1, en, a, b, val);

        Tsum[x] = Tsum[2*x] + Tsum[2*x+1];
        Tmin[x] = min(Tmin[2*x], Tmin[2*x+1]);
    }

    long long Sum_impl(int x, int beg, int en, int a, int b) {
        if(b < beg || a > en) return 0;

        if(a <= beg && en <= b) return Tsum[x];

        Propagate(x, beg, en);

        int mid = (beg + en) / 2;

        return Sum_impl(2*x, beg, mid, a, b) + Sum_impl(2*x+1, mid+1, en, a, b);
    }

    long long MinVal_impl(int x, int beg, int en, int a, int b) {
        if(b < beg || a > en) return LLONG_MAX;

        if(a <= beg && en <= b) return Tmin[x];

        Propagate(x, beg, en);

        int mid = (beg + en) / 2;

        return min(MinVal_impl(2*x, beg, mid, a, b), MinVal_impl(2*x+1, mid+1, en, a, b));
    }

    void Add(int a, int b, long long val) {
        Add_impl(1, 0, n-1, a, b, val);
    }

    long long Sum(int a, int b) {
        return Sum_impl(1, 0, n-1, a, b);
    }

    long long MinVal(int a, int b) {
        return MinVal_impl(1, 0, n-1, a, b);
    }
};