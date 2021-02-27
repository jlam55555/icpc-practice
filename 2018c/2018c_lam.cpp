#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int P, i, j, N, k, l, m;

	// get number of datasets
	cin >> P;

	vector<long long> dp = {1, 2};

	for (i = 0; i < P; i++) {
		// get dataset number
		cin >> j >> N;

		if (dp.size() <= N) {
			for (k = dp.size(); k <= N; k++) {
				m = (dp[k-1] + dp[k-2] + k%2) % 10007;
				dp.push_back(m);
			}
		}

		// print result
		cout << j << " " << dp[N] << endl;
	}

	return 0;
}