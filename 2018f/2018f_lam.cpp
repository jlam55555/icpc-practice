#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <cstring>
#include <deque>
#include <cmath>

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

		// init probabilities
		double dp[n] = {0}, dp2[n];
		dp[0] = 1;
		int sodp = sizeof dp;
		deque<double> hist;

		// iterate
		double pround = 1, ratio = pr + pl, pwin = 0;
		int round;
		for (round = 0; hist.size() < 10 || (hist.front() - hist.back()) > 1e-8; round++) {
			pround *= ratio;
			pwin += dp[k] * (1 - ratio);

			hist.push_front(pwin);
			if (hist.size() > 10) {
				hist.pop_back();
			}

			for (int j = 0; j < n; j++) {
				dp2[j] = dp[(j+1)%n] * pr + dp[(j+n-1)%n] * pl;
			}
			memcpy(dp, dp2, sodp);
		}

		printf("%d %.2f\n", K, pwin*100);
	}

	return 0;
}