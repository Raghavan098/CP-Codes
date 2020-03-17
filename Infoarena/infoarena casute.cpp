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
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("casute.in","r",stdin);freopen("casute.out","w",stdout);
#define all(c) c.begin(),c.end()
#define pii pair<int, int>

const int N = 3002;
const int inf = 1e9;
const int MOD = 666013;
int ans[N][N];
int h[N];
int n, m, x, y, nae;
vector<int> g[N];
vector<pii> arr;

int solve() {
    arr.push_back({0, 0});
    cin >> n >> m;
    h[0] = inf;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        arr.push_back({-x, i});
        h[i] = x;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    sort(1 + all(arr));

    for (int i = 1; i <= n; i++) {
        x = arr[i].second;
        ans[x][x] = x;
        for (int j = 1; j < i; j++) {
            y = arr[j].second;
            nae = 0;
            for (auto &k : g[x]) {
                if (h[nae] >  h[ans[k][y]]) {
                    nae = ans[k][y];
                }
            }
            ans[x][y] = nae;
            ans[y][x] = nae;
        }
    }
    int fans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            fans = ((fans * (n + 1)) + ans[i][j]);
            fans %= MOD;
        }
    }
    cout << fans;
    return 0;
}

int32_t main(){ _
__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
