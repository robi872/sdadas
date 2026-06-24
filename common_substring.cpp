#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
typedef long long ll;

struct Answer {
    size_t i, j, len;
};

class LongestCommonSubstring {
    string s, t;
    ll m1 = 1000000007;
    ll m2 = 1000000009;
    ll x = 263;
    vector<ll> h1_s, h2_s, p1, p2;
    vector<ll> h1_t, h2_t;

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
    LongestCommonSubstring(string s, string t) : s(s), t(t) {
        size_t max_len = max(s.size(), t.size());
        p1.assign(max_len + 1, 1);
        p2.assign(max_len + 1, 1);
        for (size_t i = 1; i <= max_len; i++) {
            p1[i] = (p1[i - 1] * x) % m1;
            p2[i] = (p2[i - 1] * x) % m2;
        }
        precompute(s, h1_s, h2_s);
        precompute(t, h1_t, h2_t);
    }

    pair<ll, ll> get_hash(size_t start, size_t len, const vector<ll>& h1, const vector<ll>& h2) {
        ll hash1 = (h1[start + len] - (p1[len] * h1[start]) % m1 + m1) % m1;
        ll hash2 = (h2[start + len] - (p2[len] * h2[start]) % m2 + m2) % m2;
        return {hash1, hash2};
    }

    Answer check(size_t len) {
        if (len == 0) return {0, 0, 0};
        
        struct pair_hash {
            size_t operator()(const pair<ll, ll>& p) const {
                return p.first ^ (p.second << 1);
            }
        };
        
        unordered_map<pair<ll, ll>, size_t, pair_hash> s_hashes;
        for (size_t i = 0; i + len <= s.size(); i++) {
            s_hashes[get_hash(i, len, h1_s, h2_s)] = i;
        }

        for (size_t j = 0; j + len <= t.size(); j++) {
            auto t_hash = get_hash(j, len, h1_t, h2_t);
            if (s_hashes.count(t_hash)) {
                return {s_hashes[t_hash], j, len};
            }
        }
        return {0, 0, 0};
    }

    Answer solve() {
        size_t low = 0, high = min(s.size(), t.size());
        Answer max_ans = {0, 0, 0};
        
        while (low <= high) {
            size_t mid = low + (high - low) / 2;
            Answer current = check(mid);
            if (current.len > 0 || mid == 0) {
                if (mid > max_ans.len) max_ans = current;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return max_ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s, t;
    while (cin >> s >> t) {
        LongestCommonSubstring lcs(s, t);
        Answer ans = lcs.solve();
        cout << ans.i << " " << ans.j << " " << ans.len << "\n";
    }
    return 0;
}
