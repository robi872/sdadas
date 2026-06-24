#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class MismatchSolver {
    string t, p;
    ll m1 = 1000000007;
    ll m2 = 1000000009;
    ll x = 263;
    vector<ll> h1_t, h2_t, p1, p2;
    vector<ll> h1_p, h2_p;

    void precompute(const string& str, vector<ll>& h1, vector<ll>& h2) {
        size_t n = str.size();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        for (size_t i = 1; i <= n; i++) {
            h1[i] = (x * h1[i - 1] + str[i - 1]) % m1;
            h2[i] = (x * h2[i - 1] + str[i - 1]) % m2;
        }
    }

public:
    MismatchSolver(string text, string pattern) : t(text), p(pattern) {
        size_t max_len = max(t.size(), p.size());
        p1.assign(max_len + 1, 1);
        p2.assign(max_len + 1, 1);
        for (size_t i = 1; i <= max_len; i++) {
            p1[i] = (p1[i - 1] * x) % m1;
            p2[i] = (p2[i - 1] * x) % m2;
        }
        precompute(t, h1_t, h2_t);
        precompute(p, h1_p, h2_p);
    }

    bool check_equal(size_t t_start, size_t p_start, size_t len) {
        if (len == 0) return true;
        ll hash1_t = (h1_t[t_start + len] - (p1[len] * h1_t[t_start]) % m1 + m1) % m1;
        ll hash1_p = (h1_p[p_start + len] - (p1[len] * h1_p[p_start]) % m1 + m1) % m1;
        if (hash1_t != hash1_p) return false;

        ll hash2_t = (h2_t[t_start + len] - (p2[len] * h2_t[t_start]) % m2 + m2) % m2;
        ll hash2_p = (h2_p[p_start + len] - (p2[len] * h2_p[p_start]) % m2 + m2) % m2;
        return hash2_t == hash2_p;
    }

    vector<int> solve(int k) {
        vector<int> pos;
        if (p.size() > t.size()) return pos;

        for (size_t i = 0; i <= t.size() - p.size(); i++) {
            int mismatches = 0;
            size_t p_idx = 0;

            while (p_idx < p.size()) {
                // Step 1: Binary Search for the next mismatch location
                size_t low = 1, high = p.size() - p_idx, match_len = 0;
                while (low <= high) {
                    size_t mid = low + (high - low) / 2;
                    if (check_equal(i + p_idx, p_idx, mid)) {
                        match_len = mid;
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }

                p_idx += match_len;
                if (p_idx < p.size()) {
                    mismatches++;
                    if (mismatches > k) break;
                    p_idx++; // Skip past the discovered mismatch char
                }
            }

            if (mismatches <= k) {
                pos.push_back(i);
            }
        }
        return pos;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    string t, p;
    while (cin >> k >> t >> p) {
        MismatchSolver solver(t, p);
        auto ans = solver.solve(k);
        cout << ans.size();
        for (int x : ans) {
            cout << " " << x;
        }
        cout << "\n";
    }
    return 0;
}
