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

// #define int ll

const int N = 1e5 + 10;
vector<int> primes(N);
vector<int> coll;
vector<int> p10(8);

struct node {
    node* child[11];
    int cnt;
    node () {
        cnt = 0;
        for (int i = 0; i < 11; i++) {
            child[i] = NULL;
        }
    }
};

node *root;

int getind(int i) {
    if (i == -1) return 10;
    return i;
}

int len(int x) {
    int ans = 0;
    while (x > 0) {
        ans++;
        x /= 10;
    }
    return ans;
}

int getith(int x, int i) {
    x /= p10[i];
    return x % 10;
}

map<vector<int>, int> cnt;
vector<int> getvec(int x, int l) {
    vector<int> no(l);
    for (int i = 0; i < l; i++) {
        no[i] = getith(x, i);
    }
    reverse(all(no));
    return no;
}


void prep() {
    root = new node();
    for (auto p : coll) {
        int m = len(p);
        for (int i = m; i <= 5; i++) {
            vector<int> no = getvec(p, i);
            for (int j = 0; j < i; j++) {
                int tmp = no[j];
                no[j] = -1;
                node* curr = root;
                for (int k = 0; k < i; k++) {
                    int kk = getind(no[k]);
                    if(curr -> child[kk] == NULL) {
                        curr -> child[kk] = new node();
                    }
                    curr = curr -> child[kk];
                }
                curr -> cnt++;
                no[j] = tmp;
            }
        }
    }
}

vector<vector<int>> ans;
int m, n;
int tot;
vector<int> lol;
int iter = 0;
int calc() {
    iter++;
    int k = 1;
    for (int i = 1; i < m; i++) {
        node* curr = root;
        for (int j = 0; j < m; j++) {
            int kk = getind(ans[i][j]);
            if (curr -> child[kk] == NULL) {
                k = 0;
                break;
            } else {
                curr = curr -> child[kk];
            }
        }
        k *= curr -> cnt;
    }
    tot = tot + k;
}

void dfs(int i, int j) {
    // tr(i, j, ans);
    if (i == m - 1 && j == m) {
        calc();
        return;
    }
    if (j >= m) {
        dfs(i + 1, 0);
        return;
    }
    if (i == 0) {
        int ind = j;
        ans[i][j] = lol[ind];
        ans[j][i] = lol[ind];
        if (j == m - 1) {
            dfs(i + 1, i + 2);
        } else {
            dfs(i, j + 1);
        }
        return;
    }
    for (int k = 0; k < 10; k++) {
        ans[i][j] = k;
        ans[j][i] = k;
        if (j == m - 1) {
            dfs(i + 1, i + 2);
        } else {
            dfs(i, j + 1);
        }
    }
    ans[i][j] = -1;
    ans[j][i] = -1;
}

void solve() {
    cin >> n;
    ans.clear();
    m = len(n);
    ans.resize(m, vector<int> (m, -1));
    tot = 0;
    lol = getvec(n, m);
    // tr(m, lol, n);
    dfs(0, 0);
    // tr(iter);
    cout << tot << endl;
}

int32_t main(){ _
    for (int i = 2; i < N; i++) {
        if (primes[i] == 0) {
            coll.push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                primes[j] = 1;
            }
        }
    }
    p10[0] = 1;
    for (int i = 1; i < 8; i++) p10[i] = p10[i - 1] * 10;
    prep();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
