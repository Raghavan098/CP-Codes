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
#define LOCAL 0
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

#define int ll

// v^2sqrt(E)
struct edge
{
	ll from, to, cap, flow, index;
	edge(ll from, ll to, ll cap, ll flow, ll index):
		from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel
{
	ll n;
	vector<vector<edge> > g;
	vector<long long> excess;
	vector<ll> height, active, count;
	queue<ll> Q;

	PushRelabel(ll n):
		n(n), g(n), excess(n), height(n), active(n), count(2*n) {}

	void addEdge(ll from, ll to, ll cap)
	{
		g[from].push_back(edge(from, to, cap, 0, g[to].size()));
		if(from==to)
			g[from].back().index++;
		g[to].push_back(edge(to, from, 0, 0, g[from].size()-1));
	}

	void enqueue(ll v)
	{
		if(!active[v] && excess[v] > 0)
		{
			active[v]=true;
			Q.push(v);
		}
	}

	void push(edge &e)
	{
		ll amt=(ll)min(excess[e.from], (long long)e.cap - e.flow);
		if(height[e.from]<=height[e.to] || amt==0)
			return;
		e.flow += amt;
		g[e.to][e.index].flow -= amt;
		excess[e.to] += amt;
		excess[e.from] -= amt;
		enqueue(e.to);
	}

	void relabel(ll v)
	{
		count[height[v]]--;
		ll d=2*n;
		for(auto &it:g[v])
		{
			if(it.cap-it.flow>0)
				d=min(d, height[it.to]+1);
		}
		height[v]=d;
		count[height[v]]++;
		enqueue(v);
	}

	void gap(ll k)
	{
		for(ll v=0;v<n;v++)
		{
			if(height[v]<k)
				continue;
			count[height[v]]--;
			height[v]=max(height[v], n+1);
			count[height[v]]++;
			enqueue(v);
		}
	}

	void discharge(ll v)
	{
		for(ll i=0; excess[v]>0 && i<g[v].size(); i++)
			push(g[v][i]);
		if(excess[v]>0)
		{
			if(count[height[v]]==1)
				gap(height[v]);
			else
				relabel(v);
		}
	}

	long long max_flow(ll source, ll dest)
	{
		count[0] = n-1;
		count[n] = 1;
		height[source] = n;
		active[source] = active[dest] = 1;
		for(auto &it:g[source])
		{
			excess[source]+=it.cap;
			push(it);
		}

		while(!Q.empty())
		{
			ll v=Q.front();
			Q.pop();
			active[v]=false;
			discharge(v);
		}

		long long max_flow=0;
		for(auto &e:g[source]) {
            // tr(e.from, e.to, e.flow, e.cap);    
			max_flow+=e.flow;
        }

		return max_flow;
	}
};


const int N = 1019;
const int M = 512;
const int inf = 1e9;
int n, k, A, B;
int arr[N];
int cost[M][M];


vector<int> a, b;

int solve() {
    cin >> k >> n >> A >> B;
    set<int> cc;
    int q = 0;
    for (int i = 0; i < A; i++) {
        int x;
        cin >> x;
        a.push_back(x);
        cc.insert(x);
    }
    for (int i = 0; i < B; i++) {
        int x;
        cin >> x;
        b.push_back(x);
        if (cc.count(x)) {
            q++;
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    int ans = 0;
    for (int i = 1; i <= n - 1; i++) {
        int x;
        cin >> x;
        int a = arr[i];
        int b = arr[i + 1];
        if (a > b) swap(a, b);
        cost[a][b] += x;
        ans += x;
    }
    PushRelabel p(2 * k + 2);

    for (int i = 0; i < A; i++) {
        p.addEdge(0, a[i], inf);
    }

    for (int i = 0; i < B; i++) {
        p.addEdge(b[i], k + 1, inf);
    }
    
    for (int i = 1; i <= k; i++) {
        for (int j = i + 1; j <= k; j++) {
            // tr(i, j, cost[i][j]);
            p.addEdge(i, j, cost[i][j]);
            p.addEdge(j, i, cost[i][j]);
        }
    }

    int t = p.max_flow(0, k + 1);

    cout << ans - t + q * inf << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
