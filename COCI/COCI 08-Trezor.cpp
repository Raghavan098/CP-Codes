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

#define int ll

int a, b, l;

int gcd(int a, int b) {
    if (a == 0) return b;
    return __gcd(a, b);
}

int lcm(int a, int b) {
    if (b < a) swap(a, b);
    int ans = a * b;
    ans /= gcd(a, b);
    return ans;
}

int cnt(int x) {
    if (x == 0) {
        return 1;
    }
    vector<int> primes;
    int curr = x;
    for (int i = 2; i * i <= x; i++) {
        if (curr % i == 0) {
            primes.push_back(i);
            while (curr % i == 0) {
                curr /= i;
            }
        }
    }
    if (curr > 1) {
        primes.push_back(curr);
    }
    // tr(x, primes);
    int tot = 0;
    int n = primes.size();
    for (int i = 0; i < (1 << n); i++) {
        int number = 1;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                number *= primes[j];
            }
        }
        if (__builtin_popcount(i) % 2 == 1) {
            tot -= (l / number);
        } else {
            tot += (l / number);
        }
        // tr(i, number, tot);
    }
    return tot;
}


int solve() {
    cin >> a >> b >> l;
    int tot = l * (a + b + 1);
    // tr(tot);
    int yes = 0, superyes = 0;
    for (int i = 0; i < (b + a + 1); i++) {
        int j = (a + b - i);
        int na = cnt(i);
        int nb = cnt(j);
        int nc = cnt(lcm(i, j));
        // tr(i, j, na, nb, nc);
        yes += (na + nb - 2 * nc);
        superyes += nc;
    }
    cout << tot - (yes + superyes) << endl;
    cout << yes << endl;
    cout << superyes << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
