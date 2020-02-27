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

// #define int ll
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
		for(auto &e:g[source])
			max_flow+=e.flow;

		return max_flow;
	}
};

int solve() {
    int n, m, c, k;
    cin >> n >> m >> c >> k;
    vector<pii> stud, stop;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        stud.push_back({x, y});
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        stop.push_back({x, y});
    }
    vector<vector<int>> buses;
    for (int i = 0; i < k; i++) {
        int ki;
        cin >> ki;
        vector<int> temp;
        for (int j = 0; j < ki; j++) {
            int x;
            cin >> x; x--;
            temp.push_back(x);
        }
        buses.push_back(temp);
    }

    int l = 0, r = 1e9;
    int mid, ans = -1;
    auto sq = [&](int x) {
        return x * x;
    };
    auto dist = [&](pii a, pii b) {
        return (sq(a.fi - b.fi) + sq(a.se - b.se));
    };
    PushRelabel ansIthink(2 + n + m + k);
    while (l <= r) {
        mid = (l + r) / 2;
        PushRelabel flow(2 + n + m + k);
        for (int i = 0; i < n; i++) {
            flow.addEdge(0, 2 + i, 1);
        }

        for (int i = 0; i < k; i++) {
            flow.addEdge(2 + n + m + i, 1, c);
        }

        for (int i = 0; i < k; i++) {
            for (auto j : buses[i]) {
                flow.addEdge(2 + n + j, 2 + n + m + i, c);
            }
        }

        // tr(l, r, mid);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // tr(i, j);
                if (dist(stud[i], stop[j]) <= mid) {
                    flow.addEdge(2 + i, 2 + n + j, 1);
                }
            }
        }

        int mxflow = flow.max_flow(0, 1);

        if (mxflow == n) {
            ans = mid;
            ansIthink = flow;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if (ans == -1) {
        cout << ans << endl;
    } else {
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            for (auto e : ansIthink.g[2 + i]) {
                if (e.flow == 1) {
                    cout << e.to - 2 - n + 1 << endl;
                    break;
                }
            }
        }
    }
    return 0;
}

int32_t main(){ 
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
