#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MOD 1000000007
struct tree
{
    vector <int> ch;
    int lvl;
};
int bfs(tree t[], int root)
{
    int max_height = 1, s, i; 
    queue <int> q;
    q.push(root);
    while(!q.empty())
    {
        s = q.front();
        q.pop();
        for(i = 0; i < t[s].ch.size(); i++)
        {
            t[t[s].ch[i]].lvl = t[s].lvl + 1;
            max_height = max(max_height, t[t[s].ch[i]].lvl);
            q.push(t[s].ch[i]);
        }
    }
    return max_height;
}
int main() 
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n,i,root,l,k;
	cin>>n;
	tree t[100005];
	for(i=0;i<n;i++)
	{
	    cin>>k;
	    if(k==-1)
	     root=i;
	    else
	     t[k].ch.push_back(i);
	}
	t[root].lvl=1;
	l=bfs(t,root);
	cout<<l;
	return 0;
}
