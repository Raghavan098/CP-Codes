/*
    Playing around with indices!!
    for each index i in each string j
    find the max over lap with substring (i..) to any other substring in any other string other than j
    after finding the max overlap let it be (i..k) and the suffix starting from i (i...q) now 
    all the substring (i...p) k + 1 <= p <= q will be unique to this string j

    all the above calculations can be taken care using the indices that is generated using the suffix array

    for finding the max over lap find the nearest index to the right and left that does not originate from the same string
    and find the max common substring these two indices using the lcp array of the suffix array

    also don't forget that only unique substrings from the same string has to be taken into count
    which again can be done using the lcp array
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
#define __ freopen("standingout.in","r",stdin);freopen("standingout.out","w",stdout);
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

#define int ll

const int N = 1e6 + 1;

/**
 * Thanks to Benq
 * Description: Sort suffixes. 
 * Time: O(N\log N)
 * Source: SuprDewd, KACTL, majk, ekzhang (http://ekzlib.herokuapp.com)
 * Verification: 
	* http://usaco.org/index.php?page=viewproblem2&cpid=768
		* https://pastebin.com/y2Z9FYr6
	* https://open.kattis.com/problems/suffixsorting
	* https://codeforces.com/contest/1090/problem/J
 */

template<class T> struct RMQ { // floor(log_2(x))
	int level(int x) { return 31-__builtin_clz(x); } 
	vector<T> v; vector<vector<int>> jmp;
	int comb(int a, int b) { // index of min
		return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); } 
	void init(const vector<T>& _v) {
        int n = _v.size();
		v = _v; jmp = {vector<int>(n)}; iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= n; ++j) {
			jmp.push_back(vector<int>(n-(1<<j)+1));
			for (int i = 0; i < (int)jmp[j].size(); i++)
                jmp[j][i] = comb(jmp[j-1][i], jmp[j-1][i+(1<<(j-1))]);
		}
	}
	int index(int l, int r) { // get index of min element
		int d = level(r-l+1);
		return comb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
	T query(int l, int r) { return v[index(l,r)]; }
};

struct SuffixArray {
	string S; int N;
	RMQ<int> R; 
	void init(const string& _S) {
		S = _S; N = S.size();
		genSa(); genLcp(); 
        R.init(lcp);
	}
	vector<int> sa, isa; // sa[i] = index of the string for ith suffix in the suffix array
	void genSa() {
		sa.resize(N), isa.resize(N); iota(all(sa),0);
		sort(all(sa),[&](int a, int b) { return S[a] < S[b]; });
		for (int i = 0; i < N; i++) {
			bool same = i && S[sa[i]] == S[sa[i-1]];
			isa[sa[i]] = same ? isa[sa[i-1]] : i; 
		}
		for (int len = 1; len < N; len *= 2) { 
			// sufs currently sorted by first len chars
			vector<int> is(isa), s(sa), nex(N); iota(all(nex),0); 
			for (int i = -1; i < N; i++) { // rearrange sufs by 2*len
				int s1 = (i == -1 ? N : s[i])-len; 
				if (s1 >= 0) sa[nex[isa[s1]]++] = s1; 
			} 
			for (int i = 0; i < N; i++) { // update isa for 2*len
				bool same = i && sa[i-1]+len < N
							  && is[sa[i]] == is[sa[i-1]]
							  && is[sa[i]+len] == is[sa[i-1]+len]; 
				isa[sa[i]] = same ? isa[sa[i-1]] : i; 
			}
		}
	}
	vector<int> lcp;
	void genLcp() { // Kasai's Algo
		lcp = vector<int>(N-1); int h = 0;
		for (int i = 0; i < N; i++) if (isa[i]) {
			for (int j=sa[isa[i]-1]; j+h<N && S[i+h]==S[j+h]; h++);
			lcp[isa[i]-1] = h; if (h) h--; 
		}
		// if we cut off first chars of two strings with lcp h 
		// then remaining portions still have lcp h-1 
	}
	int getLCP(int a, int b) { // lcp of suffixes starting at a,b
        // tr(a, b);
		if (max(a,b) >= N) return 0;
		if (a == b) return N-a;
		int t0 = isa[a], t1 = isa[b];
		if (t0 > t1) swap(t0,t1);
		return R.query(t0,t1-1);
	}
};

const int inf = 1e9 + 1;

int n;
vector<string> arr;
int ind[N];
int ans[N];
int currind[N];
int omgind[N];
int saind[N];
int lef[N], rig[N], same[N];
int tlen[N];

int solve() {
    cin >> n;
    arr.resize(n);
    string s;

    int curr = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s += '#';
        s += arr[i];
        int len = arr[i].size();
        ind[curr] = i; curr++;
        for (int j = 0; j < len; j++) {
            ind[curr] = i;
            omgind[curr] = j;
            curr++;
        }
        tlen[i] = len;
    }

    SuffixArray sa;
    sa.init(s);
    for (int i = 0; i < curr; i++) {
        saind[i] = ind[sa.sa[i]];
    }
    MEMS(currind, -1);
    set<int> st;

    for (int i = 0; i < curr; i++) {
        if (s[sa.sa[i]] == '#') continue;
        if (currind[saind[i]] != -1) st.erase(st.find(currind[saind[i]]));
        if (st.empty()) {
            lef[i] = -1;
        } else {
            lef[i] = *st.rbegin(); 
        }
        st.insert(i);
        currind[saind[i]] = i;
    }

    st.clear();
    MEMS(currind, -1);
    for (int i = curr - 1; i >= 0; i--) {
        if (s[sa.sa[i]] == '#') continue;
        if (currind[saind[i]] != -1) {
            same[i] = currind[saind[i]];
            st.erase(st.find(currind[saind[i]]));
        } else {
            same[i] = -1;
        }
        if (st.empty()) {
            rig[i] = -1;
        } else {
            rig[i] = *st.begin();
        }
        st.insert(i);
        currind[saind[i]] = i;
    }

    for (int i = 0; i < curr; i++) {
        if (s[sa.sa[i]] == '#') continue;
        int tot = 0;
        if (lef[i] != -1) {
            tot = sa.getLCP(sa.sa[lef[i]], sa.sa[i]);
        }
        if (rig[i] != -1) {
            tot = max(tot, sa.getLCP(sa.sa[i], sa.sa[rig[i]]));
        }
        if (same[i] != -1) {
            tot = max(tot, sa.getLCP(sa.sa[i], sa.sa[same[i]]));
        }
        int a = tlen[ind[sa.sa[i]]];
        int b = omgind[sa.sa[i]];
        int rem = a - b - tot;
        rem = max(rem, 0LL);
        ans[ind[sa.sa[i]]] += rem;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}

int32_t main(){ _
__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
