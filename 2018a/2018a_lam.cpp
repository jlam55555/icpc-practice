#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
	int i, j, k, l, m, n, c, pos, dp[31];
	string line, token;

	cin >> k;

	for (i = 0; i < k; i++) {
		cin >> j >> c;

		memset(dp, 0, sizeof dp);
		dp[0] = 1;

		for (l = 0; l < 10; l++) {
			cin >> n;
			for (m = 29; m >= 0; m--) {
				if (dp[m] && m + n <= c) {
					dp[m+n] = dp[m];
					if (m + n == c) {
						goto done;
					}
				}
			}
		}

		done:
		for (; l < 9; l++) {
			cin >> n;
		}
		
		cout << j << (dp[c] ? " YES" : " NO") << endl;
	}
}