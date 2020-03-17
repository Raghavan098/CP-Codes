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
#define __ freopen("peaks.in","r",stdin);freopen("peaks.out","w",stdout);
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

const int N = 2002;
const int M = 1e5 + 100;
int n, m;
map<int, vector<pii>> events;


int parent[M];
int size[M];
pii peak[M];
int needans[M];
int mxx[] = {-1, 0, 1};
int arr[N][N];
int number;
vector<pii> ans;
void make_set(int x) {
    parent[x] = x;
    size[x] = 1;
}
int find_set(int v) {
    if(v == parent[v]) {
        return v;
    }
    return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if(a != b) {
        if(size[a] < size[b]) {
            swap(a,b);
        }
        if (peak[a].fi < peak[b].fi) {
            if (needans[a] == 0 && peak[a].fi != number) {
                for (int i = 0; i < peak[a].se; i++) {
                    ans.push_back({peak[a].fi, number});
                }
            }
            peak[a].fi = peak[b].fi;
            peak[a].se = peak[b].se;
            needans[a] = needans[b];
        } else if (peak[a].fi == peak[b].fi && number != peak[a].fi) {
            peak[a].se += peak[b].se;
            needans[a] |= needans[b];
        } else if (peak[a].fi > peak[b].fi ) {
            if (needans[b] == 0 && peak[b].fi != number) {
                for (int i = 0; i < peak[b].se; i++) {
                    ans.push_back({peak[b].fi, number});
                }
                needans[b] = 1;
            }
        }
        parent[b] = a;
        size[a] += size[b];
    }
}


int solve() {
    int max_e = -1;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            events[x].push_back({i, j});
            arr[i][j] = x;
            max_e = max(max_e, x);
        }
    }

    auto valid = [](int x, int y) -> bool {
        return (x > 0 && x <= n && y > 0 && y <= m);
    };

    for (auto it = events.rbegin(); it != events.rend(); it++) {
        number = it -> first;
        vector<pii> coor = it -> second;
        for (auto p : coor) {
            int x = p.fi;
            int y = p.se;
            int kk = (x - 1) * m + y;
            make_set(kk);
            peak[kk].fi = number;
            peak[kk].se = 1;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (!valid(x + mxx[i], y + mxx[j])) continue;
                    int lol = (x + mxx[i] - 1) * m + (y + mxx[j]);
                    if (lol <= 0) continue;
                    if (lol > n * m) continue;
                    if (arr[x + mxx[i]][y + mxx[j]] > number) {
                        needans[kk] = 1;
                    } else if (arr[x + mxx[i]][y + mxx[j]] == number) {
                        needans[kk] |= needans[lol];
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (!valid(x + mxx[i], y + mxx[j])) continue;
                    int lol = (x + mxx[i] - 1) * m + (y + mxx[j]);
                    if (lol <= 0) continue;
                    if (lol > n * m) continue;
                    if (size[lol] != 0) {
                        union_sets(lol, kk);
                    }
                }
            }
        }
        if (number == max_e) {
            set<int> visit;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    int kk = (i - 1) * m + j;
                    if (size[kk] != 0) {
                        kk = find_set(kk);
                        if (!visit.count(kk)) {
                            ans.push_back({max_e, 0});
                            visit.insert(kk);
                        }
                    }
                }
            }
        }
    }
    sort(ans.rbegin(), ans.rend());
    cout << (int)ans.size() << endl;
    for (auto p : ans) {
        cout << p.fi << " " << p.se << endl;
    }
    return 0;
}

int32_t main(){ _
// __
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
