/*
    given a interval write down a formula of the probability. Now add one more element and write the probability again.
    get the condition for which the probability will increase.
    we can see that we can solve this problem using two pointers.
*/

#include<bits/stdc++.h>

typedef long long ll;
typedef long double lld;
using namespace std;

#define endl "\n"
#define fi first
#define se second
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("cowdate.in","r",stdin);freopen("cowdate.out","w",stdout);
#define all(c) c.begin(),c.end()
#define pii pair<int, int>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

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
template <typename T>
ostream &operator<<(ostream &out, multiset<T> const &v) {
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

int solve() {
    int n;
    cin >> n;
    
    vector<lld> p(n);

    for (int i = 0; i < n; i++) {
        int tp;
        cin >> tp;
        p[i] = ((tp * 1.00) / 1e6);
    }

    int r = 0;
    lld sum = 0;
    lld prod = 1.0;

    lld ans = 0;

    for (int i = 0; i < n; i++) {
        while (r < n && sum < 1) {
            lld tp = (p[r] / (1.00 - p[r]));
            sum += tp;
            prod *= (1 - p[r]);
            r++;
        }
        ans = max(ans, sum * prod);
        lld tp = (p[i] / (1.00 - p[i]));
        sum -= tp;
        prod /= (1 - p[i]);
    }
    cout << (int)(ans * 1000000) << endl;
    return 0;
}

int32_t main(){ _
__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
    return 0;	
}
