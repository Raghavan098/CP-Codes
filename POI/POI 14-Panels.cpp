/*

    -> Lets say we fix a value x to be the answer. 
    -> Our next step to check if this is valid is we will take the nearest multiple x less than or equal to b and d 
    -> Let's find the condition for b same applies for d as well
    -> lets say y * x is that nearest multiple. We know that y = floor(b/x)
    -> we know that there are only sqrt(b) different values of y. So it means there are sqrt(b) different values for x as well
    -> Now we just iterate through all the values of x and update our answer.

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
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
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
// #define int ll

int a, b, c, d;
bool can(int x) {
    int lol = (a + x - 1) / x;
    lol *= x;
    if (lol > b) return false;
    lol = (x + c - 1) / x;
    lol *= x;
    if (lol > d) return false;
    return true;
}

int solve() {
    cin >> a >> b >> c >> d;
    int x = max(b, d);
    x = ceil(sqrtl(x));
    int ans = 0;
    for (int i = 1; i <= x; i++) {
        if (can(i)) {
            ans = max(ans, i);
        }
        int t = b / i;
        if (can(t)) {
            ans = max(ans, t);
        }
        t = d / i;
        if (can(t)) {
            ans = max(ans, t);
        }
    }
    cout << ans << endl;
    return 0;
}

int32_t main(){ _
    int t;
    cin >> t;
    // t = 1;
    while (t--) solve();
}
