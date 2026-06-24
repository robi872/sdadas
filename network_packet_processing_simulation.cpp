#include <iostream>
#include <queue>
using namespace std;
typedef long long int ll;
#define MOD 1000000007
int main() 
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll s,n,i,c=0,a,p,t=0;
	queue <ll> q;
	cin>>s>>n;
    for (i = 0; i < n; i++) 
    {
    cin >> a >> p;
    while (!q.empty() && q.front() <= a) 
    {
        q.pop();
    }
    if (q.size() == s) 
    {
        cout << -1 << "\n";
    } 
    else 
    {
        if (q.empty()) 
        {
            cout << a << "\n";
            t = a + p;
        } 
        else 
        {
            cout << t << "\n";
            t = t + p;
        } 
        q.push(t);
            }
        }
	}
	return 0;
}
