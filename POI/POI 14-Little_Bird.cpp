/*

    answer is greedy, 
    if you can jump to something less than yours jump to biggest of all such elements
    if not then jump to the biggest of all the elements that you can jump to and is greater than currnt element

*/

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

const int N = 1e6 + 10;

int n, q;
int arr[N];

void insert(deque<pii> &d, pii p) {
    while (!d.empty() && d.back() < p) d.pop_back();
    d.push_back(p);
}

void popuntil(deque<pii> &d, int ptr) {
    while (!d.empty() && d.front().se < ptr) d.pop_front();
}

int solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    cin >> q;
    for (int i_ = 0; i_ < q; i_++) {
        int k; cin >> k;
        deque<pii> more, less;
        int lp = 1, rp = 1;
        int ans = 0;
        while (lp < n) {
            popuntil(more, lp);
            popuntil(less, lp);
            while (rp < n && rp - lp < k) {
                rp++;
                if (arr[rp] >= arr[lp]) {
                    insert(more, {arr[rp], rp});
                } else {
                    insert(less, {arr[rp], rp});
                }
            }
            if (!less.empty()) {
                lp = less.front().se;
                less.pop_front();
                while (!less.empty() && less.front().fi == arr[lp]) less.pop_front();
            } else if (!more.empty()) {
                ans++;
                lp = more.front().se;
                more.pop_front();
                less = more;
                more.clear();
            } else {
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
