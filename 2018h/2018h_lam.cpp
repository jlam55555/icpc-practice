#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

vector<int> primes;
unordered_set<int> primes_map;

vector<int> esieve(int n)
{
	char* composites = new char[n];
	vector<int> res;
	int sqrtn = sqrt(n), i, j;

	if (n >= 2) {
		res.push_back(2);
	}

	for (i = 3; i <= sqrtn; i+=2) {
		if (!composites[i]) {
			for (j = i*i; j < n; j+=2*i) {
				composites[j] = 1;
			}
			res.push_back(i);
		}
	}

	for (; i < n; i+=2) {
		if (!composites[i]) {
			res.push_back(i);
		}
	}

	delete composites;
	return res;
}

int sp(int n)
{
	// if 1 or n, return itself
	if (n == 1 || primes_map.count(n)) {
		return n;
	}

	// otherwise return n/p
	for (int i : primes) {
		if (n % i == 0) {
			return n / i;
		}
	}

	return -1;
}

int main()
{
	int i, n, P, K;
	unsigned long a0, a1, tmp;
	unordered_map<unsigned long, int> found{100};
	vector<int> seq{};

	// generate primes
	primes = esieve(100000);
	primes_map = unordered_set<int>(primes.begin(), primes.end());

	// get number of datasets
	cin >> P;

	for (i = 0; i < P; i++) {
		// get dataset number
		cin >> K >> n >> a0 >> a1;

		found.clear();
		found[(a0 << 32) | a1] = 0;

		seq.clear();
		seq.push_back(a0);
		seq.push_back(a1);

		int j;
		bool repeat_found = false;
		for (j = 0; j < n-1; j++) {
			tmp = a0;
			a0 = a1;
			a1 = sp(tmp + a1);
			seq.push_back(a1);

			tmp = (a0 << 32) | a1;

			if (found.count(tmp)) {
				repeat_found = true;
				break;
			}
			found[tmp] = j+1;
		}

		if (repeat_found) {
			int first_repeat = j+2, length = j+1-found[tmp];
			cout << K << " " << first_repeat << " " << length << endl;

			// print result
			for (int i = first_repeat-length-1, j = 0; j < length+2; i++, j++) {
				if (j) {
					if (j % 20 == 0) {
						cout << endl;
					} else {
						cout << " ";
					}
				}
				cout << seq[i];
			}
			cout << endl;
		} else {
			cout << K << " " << n << " 0" << endl;
			cout << a1 << endl;


		}
	}

	return 0;
}