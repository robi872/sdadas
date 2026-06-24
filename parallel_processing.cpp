#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long int ll;
#define ln "\n"

struct job {
    ll id;       
    ll next_free; 
};

void CardSiftdown(vector<job>& k, ll n, ll i) {
    ll min_idx = i;
    ll l = 2 * i + 1;
    ll r = 2 * i + 2;

    if (l < n && (k[l].next_free < k[min_idx].next_free || 
                 (k[l].next_free == k[min_idx].next_free && k[l].id < k[min_idx].id))) {
        min_idx = l;
    }
    if (r < n && (k[r].next_free < k[min_idx].next_free || 
                 (k[r].next_free == k[min_idx].next_free && k[r].id < k[min_idx].id))) {
        min_idx = r;
    }
    if (min_idx != i) {
        swap(k[i], k[min_idx]);
        CardSiftdown(k, n, min_idx);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;
    if (!(cin >> n >> m)) return 0;

    vector<ll> jobs(m);
    for (ll i = 0; i < m; i++) {
        cin >> jobs[i];
    }

   
    vector<job> threads(n);
    for (ll i = 0; i < n; i++) {
        threads[i].id = i;
        threads[i].next_free = 0;
    }

 
    for (ll i = 0; i < m; i++) {
        cout << threads[0].id << " " << threads[0].next_free << ln;

      
        threads[0].next_free += jobs[i];
        CardSiftdown(threads, n, 0);
    }

    return 0;
}
