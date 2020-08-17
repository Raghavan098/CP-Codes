/*

    The important observation is that there could be only sqrt(n) different lengths of banned strings
    hash everything and for each index check all the length's hash if it is present in the banned hashes.
    if it is then remove it.
    

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
#define __ freopen("censor.in","r",stdin);freopen("censor.out","w",stdout);
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
string s;
int n;

const int N = 1e5 + 10;
const int p1 = 31;
const int MOD1 = 1e9 + 7;

const int p2 = 101;
const int MOD2 = 1e9 + 9;

int pow1[N];
int pow2[N];

void pre_hash() {
    pow1[0] = 1;
    pow2[0] = 1;
    
    for (int i = 1; i < N; i++) {
        pow1[i] = (pow1[i - 1] * p1) % MOD1;
        pow2[i] = (pow2[i - 1] * p2) % MOD2;
    }
}

pii get_next(pii h, char c) {
    h.fi *= p1;
    h.fi %= MOD1;
    h.fi += (c - 'a' + 1);
    h.fi %= MOD1;

    h.se *= p2;
    h.se %= MOD2;
    h.se += (c - 'a' + 1);
    h.se %= MOD2;

    return h;
}

pii get_hash(string t) {
    pii hashh = {0, 0};
    int m = t.size();
    for (int i = 0; i < m; i++) {
        hashh = get_next(hashh, t[i]);
    }
    return hashh;
}

int solve() {
    pre_hash();
    cin >> s;
    cin >> n;
    vector<string> arr(n);

    unordered_map<int, set<pii>> hashes; 


    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        int m = arr[i].size();
        auto p = get_hash(arr[i]);
        hashes[m].insert(p);
        // tr(i, m, p);
    }

    string ans;
    vector<pii> curr_hash = {{0, 0}};

    int len = s.size();

    for (int i = 0; i < len; i++) {
        // tr(curr_hash.back());
        curr_hash.push_back(get_next(curr_hash.back(), s[i]));
        ans += s[i];
        // tr(ans, curr_hash.back(), i);
        for (const auto &p : hashes) {
            if ((int)curr_hash.size() <= p.fi) continue;
            pii hash_len;
            int ind = curr_hash.size();
            hash_len.fi = (curr_hash.back().fi - ((curr_hash[ind - p.fi - 1].fi * pow1[p.fi]) % MOD1) + MOD1) % MOD1;
            hash_len.se = (curr_hash.back().se - ((curr_hash[ind - p.fi - 1].se * pow2[p.fi]) % MOD2) + MOD2) % MOD2;
            // tr(i, p.fi, hash_len);
            if (p.se.count(hash_len)) {
                // tr(i, p.fi);
                curr_hash.resize(curr_hash.size() - p.fi);
                // tr(curr_hash.size());
                ans.resize(ans.size() - p.fi);
                break;
            }
        }

    }

    cout << ans << endl;

    return 0;

}

int32_t main(){ _

__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
    return EXIT_SUCCESS;	
}
