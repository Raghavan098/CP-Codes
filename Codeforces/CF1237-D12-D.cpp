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

#define sd(x) scanf("%d",&x)
#define sd2(x,y) scanf("%d%d",&x,&y)
#define sd3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define endl "\n"
#define fi first
#define se second
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define LET(x, a)  __typeof(a) x(a)
#define foreach(it, v) for(LET(it, v.begin()); it != v.end(); it++)
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define all(c) c.begin(),c.end()
#define inf 1000000000000000001

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

const int N = 1e5 + 199;

template <typename T, class F = function<T(const T&, const T&)>>
class SparseTable {
 public:
  int n;
  vector<vector<T>> mat;
  F func;

  SparseTable(const vector<T>& a, const F& f) : func(f) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(int from, int to) const {
    // tr(from, to, n);
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};


int n;
vector<int> arr;
vector<int> vis;
vector<int> ans_f;
vector<int> connect;
pair<int, int> dfs(int i) {
    // tr(i);
    if (connect[i] == -1) {
        return {(i + ans_f[i]) % n, vis[i]};
    }
    auto temp = dfs(connect[i]);
    int ans_ = 0;
    if (i < temp.se) {
        ans_ = (temp.se - i);
    }
    else {
        ans_ = (temp.se + n - i);
    }

    if (temp.fi > temp.se) {
        ans_ += (temp.fi - temp.se);
    } else {
        ans_ += (temp.fi + n - temp.se);
    }
    ans_f[i] = ans_;
    // tr(i, temp);
    // if (temp.fi < i) {
    //     temp.fi += n;
    // }
    // tr(temp);
    // ans_f[i] = (temp.fi - i);
    // if ((temp.fi % n < temp.se) && (temp.se < i)) {
    //     ans_f[i] += n;
    // }
    connect[i] = -1;
    vis[i] = temp.se;
    return temp;
}

int32_t main(){
    cin >> n;
    arr.resize(2 * n + 1);
    vis.resize(2 * n + 1, -1);
    ans_f.resize(n + 1, -1);
    connect.resize(n + 1, -1);
    int mx = -1;
    int mi_ele = inf;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        mi_ele = min(mi_ele, arr[i]);
        mx = max(mx, arr[i]);
    }
    if (mi_ele >= ((lld)mx / 2.0)) {
        for (int i = 0; i < n; i++) {
            cout << -1 << " ";
        } cout << endl;
        return 0;
    }
    for (int i = n; i < 2 * n; i++) {
        arr[i] = arr[i % n];
    }
    arr[2 * n] = inf;
    auto mi = [](int a, int b) -> int{
        return min(a, b);
    };
    auto mx_t = [](int a, int b) -> int{
        return max(a, b);
    };
    SparseTable<int> s(arr, mi);
    SparseTable<int> s2(arr, mx_t);
    for (int i = 0; i < n; i++) {
        int l = i + 1, r = 2 * n;
        int mid, ans = -1;
        while (l <= r) {
            mid = (l + r) / 2;
            if (s2.get(i + 1, mid) >= arr[i]) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        l = i, r = 2 * n;
        int ans_2 = inf;
        while (l <= r) {
            mid = (l + r) / 2;
            if (s.get(i, mid) < lld((lld)arr[i] / 2.0)) {
                ans_2 = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        // tr(i, ans, ans_2, s2.get(i + 1, ans));
        if (ans_2 < ans) {
            ans_f[i] = (ans_2 - i);
        }
        else {
            connect[i] = ans;
        }
    }
    for (int i = 0; i < n; i++) {
        if (connect[i] == -1) {
            vis[i] = i;
        }
        else {
            connect[i] %= n;
        }
    }
    // tr(connect, ans_f);
    for (int i = 0; i < n; i++) {
        if (ans_f[i] == -1) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans_f[i] << " ";
    } cout << endl;
}
