/*
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2002
*/

#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>

typedef long long ll;
typedef long double lld;
using namespace std;


int n;

vector<int> get(vector<int> x, vector<int> sign) {
    sort(x.begin(), x.end());
    int cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        if (sign[i] == sign[i + 1]) cnt++;
    }
    // tr(sign, x, cnt);
    vector<int> ans(n);
    ans[0] = sign[0] * x[cnt];
    int lp = cnt;
    int rp = cnt;
    int ls = sign[0];
    int rs = sign[0];
    int cs = sign[0];
    for (int i = 1; i < n; i++) {
        if (cs == sign[i]) {
            lp--;
            if (ls == 1) {
                ans[i] = -1 * x[lp];
                ls = -1;
            } else {
                ans[i] = x[lp];
                ls = 1;
            }
        } else {
            rp++;
            // tr(rp, x[rp]);
            if (rs == 1) {
                ans[i] = -1 * x[rp];
                rs = -1; 
            } else {
                ans[i] = x[rp];
                rs = 1;
            }
        }
        cs = sign[i];
    }

    // tr(ans);

    return ans;

}

int solve() {
    cin >> n;

    vector<int> x(n);
    vector<int> y(n);
    vector<int> xsign(n);
    vector<int> ysign(n);

    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }

    for (int i = 0; i < n; i++) {
        int r;
        cin >> r;
        if (r == 4 || r == 1) {
            xsign[i] = 1;
        } else {
            xsign[i] = -1;
        }

        if (r == 1 || r == 2) {
            ysign[i] = 1;
        } else {
            ysign[i] = -1;
        }
    }

    vector<int> xans = get(x, xsign);
    vector<int> yans = get(y, ysign);

    for (int i = 0; i < n; i++) {
        cout << (xans[i] > 0 ? "+" : "-") << abs(xans[i]) << " " << (yans[i] > 0 ? "+" : "-") << abs(yans[i]) << '\n';
    }

    return 0;
}

int main(){ 
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
    return 0;	
}
