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
#define __ freopen("dictionary.in","r",stdin);freopen("dictionary.out","w",stdout);
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

const int A = 26;

// #define int ll 

struct node {
    int nxt[A];
    node() {
        for (int i = 0; i < A; i++) {
            nxt[i] = -1;
        }
    }
};

vector<node> pref, suff;

void add(vector<node> &trie, string s) {
    int n = s.size();
    int curr = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        int idx;
        if (trie[curr].nxt[c] == -1) {
            idx = trie.size();
            trie[curr].nxt[c] = idx;
            trie.push_back(node());
        } else {
            idx = trie[curr].nxt[c];
        }
        curr = idx;
    }
}

int start[A];

void pre_process() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int f = q.front();
        q.pop();
        for (int i = 0; i < A; i++) {
            if (suff[f].nxt[i] != -1) {
                q.push(suff[f].nxt[i]);
                if (f > 0) start[i]++;
            }
        }
    }
}

ll calc() {
    queue<int> q;
    q.push(0);
    ll ans = 0;
    while (!q.empty()) {
        int f = q.front();
        q.pop();
        if (f > 0) {
            ans += (suff.size() - 1);
        }
        for (int i = 0; i < A; i++) {
            if (pref[f].nxt[i] != -1) {
                q.push(pref[f].nxt[i]);
                if (f > 0) {
                    ans -= start[i];
                }
            }
        }
    }
    return ans;
}
int n, m;
int solve() {
    cin >> n;
    pref.clear(); suff.clear(); 
    for (int i = 0; i < A; i++) {
        start[i] = 0;
    }
    pref.push_back(node());
    suff.push_back(node());
    int lool = 0;
    set<int> ss;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if ((int)s.size() == 1) {
            ss.insert(int(s[0] - 'a'));
        }
        add(pref, s);
        reverse(all(s));
        add(suff, s);
    }
    pre_process();
    cout << calc() + (int)ss.size() << endl;
    return 1;
}

int32_t main(){ 
    _
    __
    solve();
}
