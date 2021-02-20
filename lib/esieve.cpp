#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

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

set<int> esieve_set(int n)
{ 
	vector<int> primes = esieve(n);
	return set<int>(primes.begin(), primes.end());
}

unordered_set<int> esieve_uset(int n)
{ 
	vector<int> primes = esieve(n);
	return unordered_set<int>(primes.begin(), primes.end());
}

bool is_prime(int n)
{
	int i, sqrtn = sqrt(n);

	if (n == 2) {
		return true;
	}
	if (n % 2 == 0) {
		return false;
	}

	for (i = 3; i <= sqrtn; i += 2) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}