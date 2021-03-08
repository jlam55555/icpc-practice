#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;

int main()
{
	int p, q, M, N, g;
	double r;

	cin >> p >> q >> N >> M;

	int sum;
	int bestsum = INT_MAX;
	int bestr = -1, bestg = -1;
	// for (sum = N; sum <= M; ++sum) {
		// cout << "trying sum " << sum << endl;
		for (g = 1; g < M; ++g) {
			int a = p;
			int b = 2*g*(p-q)-p;
			int c = p*g*g-p*g;

			double tmp = sqrt(b*b-4*a*c);
			r = (-b - tmp)/2/a;
			// if (r <= 0) {
			// 	r = (-b+tmp)/2/a;
			// }
			// cout << "r=" << r << " g=" << g << endl;
			sum = (r+g);
			if (r > 0 && r <= g && r + g >= N && r == round(r) && sum < bestsum) {
				// goto found;
				bestsum = r+g;
				bestr = r;
				bestg = g;
			}
			r = (-b+tmp)/2/a;
			sum = (r+g);
			if (r > 0 && r <= g && r + g >= N && r == round(r) && sum < bestsum) {
				// goto found;
				bestsum = r+g;
				bestr = r;
				bestg = g;
			}
			// for (r = 1; r <= g; ++r) {
			// }
		}
	// }

	// if (sum > M) {
	if (bestsum > M) {
		cout << "NO SOLUTION" << endl;
		return 0;
	}
	// 	return 0;
	// }

found:

	cout << bestr << " " << bestg << endl;
	return 0;
}