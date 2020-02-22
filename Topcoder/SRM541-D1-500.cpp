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
typedef long long ll;
typedef long double lld;
using namespace std;

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
                valid.insert(p + ori - j - 1);
            }
            p += ori;
        }
        // tr(i, valid);
    }
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


int32_t main() {
    string _a, _b, _c, _s, _f;
    int kk;
    cin >> _a >> _b >> _c >> _s >> _f >> kk;
    AkariDaisukiDiv1 lool;
    tr(lool.countF(_a, _b, _c, _s, _f, kk));
}