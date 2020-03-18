/*
        We start building the string from the start, while maintaining the sorted order of the letters
        for example if the string abcaab
        then the sorted order of the letters in the beginning is (a, b, c)
        so now we can be sure that our answer string will start with 'a'
        after that our current answer will be "a" and the sorted order will be (b, c, a)

        next step:
        ans = "ab", sorted order = (c, a, b)
        ans = "abc", sorted order = (a, b)
        ans = "abca", sorted order = (a, b)
        ans = "abacaa", sorted order = (b)
        ans = "abacaab"

        the trick to maintain the sorted order is that, l1 appears before l2 only if l1 appears before all the occurance of l2.
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

string ans;
int n, s;
int cnt[30];
int ask(string s) {
    cout << s << endl;
    fflush(stdout);
    int x;
    cin >> x;
    return x;
}

string generate(char c, int x) {
    string ans = "";
    for (int i = 0; i < x; i++) {
        ans += c;
    }
    return ans;
}

vector<char> curr;

bool before(int i, int j) {
    // tr(ans, curr, i, j);
    string temp = ans;
    temp += curr[i];
    int sec = curr[j] - 'a';
    for (int k = 0; k < cnt[sec]; k++) {
        temp += curr[j];
    }
    if ((int)temp.size() > n) return false;
    int l = ask(temp);
    return (l == (int)temp.size());
}

int solve() {
    cin >> n >> s;

    for (int i = 0; i < s; i++) {
        char c = i + 'a';
        cnt[i] = ask(generate(c, n));
        curr.push_back(c);
    }

    for (int i = 0; i < s; i++) {
        for (int j = i + 1; j < s; j++) {
            if (!before(i, j)) {
                swap(curr[i], curr[j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        ans += curr[0];
        int c = curr[0] - 'a';
        cnt[c]--;
        for (int j = 1; j < s; j++) {
            curr[j - 1] = curr[j];
        }
        curr[s - 1] = c + 'a';
        int l = 0, r = s - 2;
        int ans = s - 1;
        int mid;
        while (l <= r) {
            mid = (l + r) / 2;
            if (before(s - 1, mid)) {
                ans = mid, r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        for (int i = s - 2; i >= ans; i--) {
            curr[i + 1] = curr[i];
        }
        curr[ans] = c + 'a';
    }
    ask(ans);
    // tr(ans);
    return 0;

}

int32_t main(){ 
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
