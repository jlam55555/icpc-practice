#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <cstring>

using namespace std;

int main()
{
	int P, K, _round, n, k;
	double pl, pr;

	// get number of datasets
	cin >> P;

	for (_round = 0; _round < P; _round++) {
		// get dataset number
		cin >> K >> n >> k >> pl >> pr;

		cout << "STARTED" << endl;

		// init probabilities
		double dp[n] = {0}, dp2[n];
		dp[0] = 1;
		int sodp = sizeof dp;

// 0 1 2 3
// --------
// 1 0 0 0         1        P(2 wins) = 0
// 0 0.6 0 0.3     0.9        P(2 wins) = 0
// 0.36 0 0.45 0   0.81       P(2 wins) = 0.45

		// iterate
		double pround = 1, ratio = pr + pl, pwin = 0;


		for (int round = 0; round <= 1000; round++) {
			pround *= ratio;
			pwin += dp[k] * (1 - ratio);
			for (int j = 0; j < n; j++) {
				dp2[j] = dp[(j+1)%n] * pl + dp[(j+n-1)%n] * pr;
			}
			memcpy(dp, dp2, sodp);
			

			// cout << "ROUND " << round;
			// for (int j = 0; j < n; j++) {
			// 	printf(" %.10f", dp[j]);
			// }
			// cout << " " << pwin << endl;
		}

		// print result
		//cout << K << " " << (pwin*100 << endl;
		printf("%d %f\n", K, pwin*100);
	}

	return 0;
}