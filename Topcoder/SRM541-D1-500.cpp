#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
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


class AkariDaisukiDiv1 {
public:
	int countF(string, string, string, string, string, int);
};

const int MOD = 1e9 + 7;

ll totlen[60];
int p, q, r, n, m;
string a, b, c, s, f;

string hack = "";

char get(int x, ll ind) {

    if (x == 0) {
        if (ind >= n) return '*';
        return s[ind];
    }

    ll len = totlen[x];
    if (ind >= len) return '*';

    ll p1 = p;
    ll p2 = p1 + totlen[x - 1];
    ll p3 = p2 + q;
    ll p4 = p3 + totlen[x - 1];
    ll p5 = p4 + r;
    if (ind < p1) {
        return a[ind];
    }

    if (ind < p2) {
        return get(x - 1, ind - p1);
    }

    if (ind < p3) {
        return b[ind - p2];
    }

    if (ind < p4) {
        return get(x - 1, ind - p3);
    }

    if (ind < p5) {
        return c[ind - p4];
    }

    return '*';
}

ll calc(int x) {
    set<ll> valid;
    ll p = 0, ori = totlen[x - 1];
    for (int i = 0; i < (int)hack.size(); i++) {
        if (hack[i] != '@') {
            valid.insert(p);
            p++;
        } else {
            for (int j = 0; j < ori && j < m; j++) {
                valid.insert(p + ori - j);
            }
            p += ori;
        }
        // tr(i, valid);
    }
    // tr(valid);
    for (int i = 0; i < totlen[x]; i++) {
        cout << get(x, i);
    }
    cout << endl;
    ll ans = 0;
    for (auto i : valid) {
        string curr = "";
        for (int j = 0; j < m; j++) {
            curr += get(x, i + j);
        }
        if (curr == f) {
        	
            ans++;
        }
    }
    return ans;
}

int AkariDaisukiDiv1::countF(string Waai, string Akari, string Daisuki, string S, string F, int k) {
    a = Waai, b = Akari, c = Daisuki, s = S, f = F;
    ll prevans = 0;
    p = Waai.size();
    q = Akari.size();
    r = Daisuki.size();
    n = S.size();
    m = F.size();
    totlen[0] = n;
    hack = a + '@' + b + '@' + c;
    for (int i = 0; i < n - m + 1; i++) {
        if (F == S.substr(i, m)) {
            prevans++;
        }
    }

    for (int i = 1; i < 51; i++) {
        totlen[i] = totlen[i - 1] * 2 + p + q + r;
    }
    ll ans = 0;
    ll prevtemp = 0;
    for (int i = 1; i <= k; i++) {
        ll temp;
        if (i <= 50) {
            temp = calc(i);
        } else {
            temp = prevtemp;
        }
        ans = (2LL * prevans % MOD  + temp) % MOD;
        // tr(ans, prevans, temp);
        prevtemp = temp;
        prevans = ans;
    }
    return ans % MOD;
}

int main() {
    string _a, _b, _c, _s, _f;
    int kk;
    cin >> _a >> _b >> _c >> _s >> _f >> kk;
    AkariDaisukiDiv1 a;
    tr(a.countF(_a, _b, _c, _s, _f, kk));
    return 0;
}