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
#define __ freopen("permsort2.in","r",stdin);freopen("permsort2.out","w",stdout);
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

#define int ll

struct bit{		// use 1 based indices!!!
	int n; vector<int> tree;
	bit(int n) : n(n) { tree.assign(n + 1, 0); }
	int query(int l, int r) { return query(r) - query(l - 1); }
	int query(int r) {
		int s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, int v) {
		for(; i <= n; i += (i & (-i))) tree[i] += v;
	}
};

const int N = 1e5 + 10;
int arr[N], pos[N];

int solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        pos[arr[i]] = i;
    }   
    bit b(n);
    vector<int> ans;
    for (int i = n; i >= 1; i--) {
        int curp = pos[i] + b.query(pos[i], n);
        // tr(i, curp);
        if (curp > 1) {
            if (curp - 1 > 1) {
                ans.push_back(curp - 1);
            }
            ans.push_back(curp);
        }
        b.update(pos[i], 1);
    }

    cout << (int)ans.size() << endl;
    for (auto i : ans) {
        cout << "P " << i << endl;

    }

    return 0;

}


int32_t main(){ _
__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
