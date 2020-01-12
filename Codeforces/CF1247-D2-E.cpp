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
#define inf 1000000000000000001
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
 
#define int ll
 
const int N = 2010;
const int MOD = 1e9 + 7;
 
struct bit{		// use 1 based indices!!!
	int n; vector<int> tree;
	bit(int n) : n(n) { tree.assign(n + 1, 0); }
	int query(int l, int r) { return (((query(r) - query(l - 1)) % MOD + MOD) % MOD); }
	int query(int r) {
		int s = 0;
		for(; r > 0; r -= (r & (-r))) {
            s += tree[r];
            s %= MOD;
        } 
		return s;
	}
	void update(int i, int v) {
		for(; i <= n; i += (i & (-i))) {
            tree[i] += v;
            tree[i] %= MOD;
        }
	}
};
 
 
int cnth[N][N], cntv[N][N];
int dp[N][N][2];
 
vector<bit> dph(N, bit(N));
vector<bit> dpv(N, bit(N));
 
int n, m;
vector<string> arr(N);
 
int geth(int i, int l, int r) {
    int ans = cnth[i][l]- cnth[i][r + 1];
    return ans;
}
 
int getv(int j, int l, int r) {
    int ans = cntv[l][j] - cntv[r + 1][j];
    return ans; 
}
 
int32_t main(){ _
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string temp;
        cin >> temp;
        temp = '.' + temp;
        arr[i] = temp;
    }
    if (n == 1 && m == 1) {
        if (arr[1][1] == 'R') {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            if ((j + 1) <= m && arr[i][j + 1] == 'R') {
                cnth[i][j]++;
            }
            cnth[i][j] += cnth[i][j + 1];
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = n; i >= 1; i--) {
            if ((i + 1) <= n && arr[i + 1][j] == 'R') {
                cntv[i][j]++;
            }
            cntv[i][j] += cntv[i + 1][j];
        }
    }
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1 && arr[i][j] == '.') {
                dp[i][j][0] = 1;
                dp[i][j][1] = 1;
                dpv[i].update(j, 1);
                dph[j].update(i, 1);
                continue;
            }
            int poss = (m - j - cnth[i][j]);
            int l = 1, r = j - 1;
            int mid, ans = -1;
            // tr(i, j);
            while (l <= r) {
                mid = (l + r) / 2;
                if (geth(i, mid, j - 1) <= poss) {
                    ans = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (ans != -1)
                dp[i][j][0] = dpv[i].query(ans, j - 1);
            poss = (n - i - cntv[i][j]);
            l = 1, r = i - 1;
            ans = -1;
            while (l <= r) {
                mid = (l + r) / 2;
                if (getv(j, mid, i - 1) <= poss) {
                    ans = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (ans != -1)
                dp[i][j][1] = dph[j].query(ans, i - 1);
            // tr(ans, poss, dp[i][j][1]);
            dpv[i].update(j, dp[i][j][1]);
            dph[j].update(i, dp[i][j][0]);
        }
    }
    cout << (dp[n][m][0] + dp[n][m][1]) % MOD << endl;
}