#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int cs[26] = {0};

int main(void)
{
	string s;

	cin >> s;

	for (int i = 0; i < s.length(); ++i) {
		char c = s[i] - 'a';

		// cout << i << " " << ((int) cs[c]) << endl;

		if (cs[c] == 5){ 
			cout << "NO" << endl;
			return 0;
		} else if (cs[c]) {
			if (i%2 == cs[c]%2) {
				// cout << "i=" << i << " c=" << ((int) c) << endl;
				cout << "NO" << endl;
				return 0;
			}
			cs[c] = 5;
		} else {
			cs[c] = i%2 ? 1 : 2;
		}
	}

	cout << "YES" << endl;
	return 0;
}