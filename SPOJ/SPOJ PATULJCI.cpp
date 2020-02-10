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
#define inf 1000000000000000001
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

const int N = 3e5 + 100;
const int II = 40;

vector<vector<int>> ind(N);
int n, arr[N], c;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}


int get(int x, int a, int b) {
    int l = 0, r = ind[x].size() - 1;
    int mid, ans = -1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (ind[x][mid] >= a) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (ans == -1) return 0;
    int ans2 = -1;
    l = 0, r = ind[x].size() - 1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (ind[x][mid] <= b) {
            ans2 = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    // tr(x, ind[x], a, b, ans, ans2);
    assert(ans2 != -1);

    return (ans2 - ans + 1);
}

int solve() {
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        arr[i] = x;
        ind[x].push_back(i);
    }
    int q;
    cin >> q;
    for (int it = 0; it < q; it++) {
        int l, r;
        cin >> l >> r;
        int p = ((r - l + 1) / 2) + 1;
        int found = -1;
        for (int k = 0; k < II; k++) {
            int curr = rand(l, r);
            int cnt = get(arr[curr], l, r);
            if (cnt >= p) {
                found = arr[curr];
                break;
            }
        }
        if (found != -1) {
            cout << "yes " << found << endl;
        } else {
            cout << "no\n";
        }
    }
    return 0;
}   

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
