#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    cin >> data.pattern >> data.text;
    return data;
}

ull hash_function(const string& s, const ull &prime, const ull &x) {
    ull hash = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
        hash = (hash * x + s[i]) % prime;
    return hash;
}

vector<ull> PreComputeHash(const string& T, size_t pattern_size, const ull &prime, const ull &x) {
    size_t text_size = T.size();
    vector<ull> H(text_size - pattern_size + 1);
    
    string last_window = T.substr(text_size - pattern_size, pattern_size);
    H[text_size - pattern_size] = hash_function(last_window, prime, x);

    ull y = 1;
    for (size_t i = 1; i <= pattern_size; i++) {
        y = (y * x) % prime;
    }

    for (int i = static_cast<int>(text_size - pattern_size) - 1; i >= 0; --i) {
        long long current_hash = (long long)((H[i + 1] * x) + T[i] - (y * T[i + pattern_size]));
        // Wraps negative intermediate bounds into a safe positive range
        H[i] = (ull)((current_hash % (long long)prime + prime) % prime);
    }

    return H;
}

void RibinKarp(const Data& input) {
    const string& p = input.pattern;
    const string& t = input.text;

    ull prime = 1000000007; 
    ull x = 263;

    size_t pattern_size = p.size();
    size_t text_size = t.size();

    if (pattern_size > text_size) return;

    ull pattern_hash = hash_function(p, prime, x);
    vector<ull> H = PreComputeHash(t, pattern_size, prime, x);

    for (size_t i = 0; i <= text_size - pattern_size; ++i) {
        if (H[i] == pattern_hash) {
            // Direct index scan to eliminate temporary heap allocations
            bool match = true;
            for (size_t j = 0; j < pattern_size; ++j) {
                if (t[i + j] != p[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << i << " ";
            }
        }
    }
    cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Data data = read_input();
    RibinKarp(data);

    return 0;
}
