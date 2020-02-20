// g++ -std=c++14

/*

Today might be the chance to grasp the chance to let your talent bloom.
May be tomorrow, the day after, or next year...
May be even when you are 30. I'm not sure if physique has anything to do with it
but if you think that it will never come, it probably never will.

- Tooru Oikawa.

*/


#include<bits/stdc++.h>

typedef long long ll;
typedef long double lld;
using namespace std;

#define endl "\n"
#define fi first
#define se second
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define all(c) c.begin(),c.end()
#define pii pair<int, int>
#define tr(...) cout<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)
template<typename S, typename T>
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.fi<<", "<<p.se<<')';return out;}

template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
ll l=v.size();for(ll i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}

template <typename T>
ostream &operator<<(ostream &out, set<T> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << (*i) << ' ';
    return out;
}
template <typename T, typename V>
ostream &operator<<(ostream &out, map<T, V> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << "\n" << (i->first) <<  ":"  << (i->second);
    return out;
}

template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}

template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}

//1 indexed Hopcroft-Karp Matching in O(E sqrtV)

struct Hopcroft_Karp
{
	static const int inf = 1e9;

	int n;
	vector<int> matchL, matchR, dist;
	vector<vector<int> > g;
	vector<vector<int>> tg;
	Hopcroft_Karp(int n) :
		n(n), matchL(n+1), matchR(n+1), dist(n+1), g(n+1), tg(n + 1){}

	void addEdge(int u, int v)
	{
		tg[u].push_back(v), tg[v].push_back(u);
		g[u].push_back(v);
	}

	bool bfs()
	{
		queue<int> q;
		for(int u=1;u<=n;u++)
		{
			if(!matchL[u])
			{
				dist[u]=0;
				q.push(u);
			}
			else
				dist[u]=inf;
		}
		dist[0]=inf;

		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(auto v:g[u])
			{
				if(dist[matchR[v]] == inf)
				{
					dist[matchR[v]] = dist[u] + 1;
					q.push(matchR[v]);
				}
			}
		}

		return (dist[0]!=inf);
	}

	bool dfs(int u)
	{
		if(!u)
			return true;
		for(auto v:g[u])
		{
			if(dist[matchR[v]] == dist[u]+1 &&dfs(matchR[v]))
			{
				matchL[u]=v;
				matchR[v]=u;
				return true;
			}
		}
		dist[u]=inf;
		return false;
	}

	int max_matching()
	{
		int matching=0;
		while(bfs())
		{
			for(int u=1;u<=n;u++)
			{
				if(!matchL[u])
					if(dfs(u))
						matching++;
			}
		}
		return matching;
	}
};

vector<int> visited;

int r, c, n;

void dfs(int v, Hopcroft_Karp &h) {

	if (visited[v] == 1) return;
	// tr(v, h.tg[v]);
	visited[v] = 1;
	for (auto u : h.tg[v]) {
		if (v <= r && h.matchL[v] != u) {
			dfs(u, h);
		} else if (v > r && h.matchR[v] == u) {
			dfs(u, h);
		}
	}
}

int32_t main(){ _
    cin >> r >> c >> n;
    while (!(r + c + n == 0)) {
		visited.clear();
		visited.resize(r + c + 2);
        Hopcroft_Karp h(r + c);
        for (int i = 1; i <= n; i++) {
            int x, y;
            cin >> x >> y;
            h.addEdge(x, r + y);
        }
        int ans = h.max_matching();
		vector<int> start;
		for (int i = 1; i <= r; i++) {
			if (h.matchL[i] == 0) {
				start.push_back(i);
			}
		}
		// tr(start);
		for (auto i : start) {
			if (!visited[i]) {
				dfs(i, h);
			}
		}
		cout << ans << " ";

		for (int i = 1; i <= r; i++) {
			if (!visited[i]) {
				cout << "r" << i << " ";
			}
		}
		for (int i = r + 1; i <= r + c; i++) {
			if (visited[i]) {
				cout << "c" << i - r << " ";
			}
		}
        cout << endl;
        cin >> r >> c >> n;
    }
}
