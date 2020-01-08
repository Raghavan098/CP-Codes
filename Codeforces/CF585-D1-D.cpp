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
#define inf 1000000001
#define pii pair<int, int>
#define tr(...) cout<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)

template<typename S, typename T>
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.fi<<", "<<p.se<<')';return out;}

template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
ll l=v.size();for(ll i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}

template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}

template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}

// #define int ll

const int N = 26;

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 
  

int n, m;
vector<vector<int>> init;
map<pii, int> ezz, bzz;
int done = -inf;
int ans1, ans2;
void recurse(int ind, int val, int a, int b, int c) {
    if (ind == m) {
        int p1 = a - b;
        int p2 = b - c;
        auto tt = mp(p1, p2);
        
        if (ezz[tt] < (a + inf)) {
            ezz[tt] = a + inf;
            bzz[tt] = val;
        }
        return;
    }
    recurse(ind + 1, val * 3, a + init[ind][0], b + init[ind][1], c);
    recurse(ind + 1, val * 3 + 1, a + init[ind][0], b, c + init[ind][2]);
    recurse(ind + 1, val * 3 + 2, a, b + init[ind][1], c + init[ind][2]);
}

void recurse2(int ind, int val, int a, int b, int c) {
    if (ind == n) {
        int p1 = b - a;
        int p2 = c - b;
        auto tt = mp(p1, p2);
        if (!ezz.count(tt)) {
            return;
        } else {
            int tmp = ezz[tt] + a - inf;
            if (tmp > done) {
                done = tmp;
                ans1 = bzz[tt];
                ans2 = val;
            }
        }
        return;
    }
    recurse2(ind + 1, val * 3, a + init[ind][0], b + init[ind][1], c);
    recurse2(ind + 1, val * 3 + 1, a + init[ind][0], b, c + init[ind][2]);
    recurse2(ind + 1, val * 3 + 2, a, b + init[ind][1], c + init[ind][2]);
}

char inv[3] = {'L', 'M', 'W'};

int32_t main(){ 
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        init.push_back({a, b, c});
    }
    m = n / 2;
    vector<pii> arr;
    vector<int> abc = {0, 0, 0};
    recurse(0, 0, 0, 0, 0);
    recurse2(m, 0, 0, 0, 0);
    // tr(done, ans1, ans2);
    if (done == -inf) {
        cout << "Impossible" << endl;
    } else {
        vector<string> arr1, arr2;
        for (int i = 0; i < m; i++) {
            int lol = ans1 % 3;
            if (lol == 0) {
                arr1.pb("LM");
            } else if (lol == 1) {
                arr1.pb("LW");
            } else {
                arr1.pb("MW");
            }
            ans1 /= 3;
        }
        reverse(all(arr1));
        for (int i = m; i < n; i++) {
            int lol = ans2 % 3;
            if (lol == 0) {
                arr2.pb("LM");
            } else if (lol == 1) {
                arr2.pb("LW");
            } else {
                arr2.pb("MW");
            }
            ans2 /= 3;
        }
        reverse(all(arr2));
        for (auto i : arr1) {
            cout << i << endl;
        }
        for (auto i : arr2) {
            cout << i  << endl;
        }
    }
}
