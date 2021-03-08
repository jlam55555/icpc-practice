#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	int P, K, _round;

	// get number of datasets
	cin >> P;

	for (_round = 0; _round < P; ++_round) {
		// get dataset number (and other necessary data)
		cin >> K;

		// print result
		cout << K << " " << 42 << endl;
	}

	return 0;
}