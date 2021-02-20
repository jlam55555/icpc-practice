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

unordered_set<int> esieve_uset(int n)
{ 
	vector<int> primes = esieve(n);
	return unordered_set<int>(primes.begin(), primes.end());
}

int sp(int n)
{
	int i;

	// if 1 or n, return itself
	if (n == 1 || primes_map.count(n)) {
		return n;
	}

	// otherwise return n/p
	for (i = 0; i < primes.size(); i++) {
		if (n % i == 0) {
			return n / i;
		}
	}

	return -1;
}

int main()
{
	int i, n, P, K;
	unsigned long a0, a1;
	unordered_map<unsigned long, int> found{100};
	vector<int> seq{};

	// get number of datasets
	cin >> P;

	for (i = 0; i < P; i++) {
		// get dataset number
		cin >> K >> n >> a0 >> a1;

		found.clear();
		found.insert((a0 << 32) | a1, 0);

		seq.clear();
		seq.push_back(a0);
		seq.push_back(a1);

		int j;
		for (j = 0; j < n-2; j++) {
			a0 = a1;
			a1 = sp(a0 + a1);

			int tmp = (a0 << 32) | a1;

			if (found.count(tmp)) {
				cout << K << " " << (j+1) << " " << (j+1-found[tmp]) << endl;
				break;
			}
			found.insert(tmp, j+1);
		}

		// print result
		for (int i : seq) {
			cout << " " << i;
		}
		cout << endl;
	}

	return 0;
}