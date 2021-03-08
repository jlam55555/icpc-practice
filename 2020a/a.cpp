#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	unsigned long long P, K, _round;

	// get number of datasets
	// cin >> P;
	P = 6;

	unsigned long long  sum = 0;

	for (_round = 0; _round < P; ++_round) {
		// get dataset number (and other necessary data)
		cin >> K;

		sum += K;

		// print result
		// cout << K << " " << 42 << endl;
	}

	cout << (sum * 5) << endl;

	return 0;
}