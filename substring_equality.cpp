#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class Solver {
    string s;
    int n;
    ll m1 = 1000000007;
    ll m2 = 1000000009;
    ll x = 263;
    vector<ll> h1, h2;
    vector<ll> p1, p2;

public:    
    Solver(string s) : s(s), n(s.size()) {    
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            p1[i] = (p1[i - 1] * x) % m1;
            p2[i] = (p2[i - 1] * x) % m2;
            h1[i] = (x * h1[i - 1] + s[i - 1]) % m1;
            h2[i] = (x * h2[i - 1] + s[i - 1]) % m2;
        }
    }

    bool ask(int a, int b, int l) {
        ll hash_a1 = (h1[a + l] - (p1[l] * h1[a]) % m1 + m1) % m1;
        ll hash_b1 = (h1[b + l] - (p1[l] * h1[b]) % m1 + m1) % m1;
        if (hash_a1 != hash_b1) return false;

        ll hash_a2 = (h2[a + l] - (p2[l] * h2[a]) % m2 + m2) % m2;
        ll hash_b2 = (h2[b + l] - (p2[l] * h2[b]) % m2 + m2) % m2;
        return hash_a2 == hash_b2;
    }
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    int q;
    if (cin >> s >> q) {
        Solver solver(s);
        for (int i = 0; i < q; i++) {
            int a, b, l;
            cin >> a >> b >> l;
            cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
        }
    }
    return 0;
}
