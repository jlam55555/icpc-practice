#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    
	int P,K,C,temp;
	cin >> P;
	bool right = false;
	string line;

	unordered_set<int> pots;
	for ( int i=0; i<P; i++ ) {

		right = false;
		cin >> K >> C;
		getline(cin,line);
		istringstream iss(line);
		pots.insert(0);
		while( iss >> temp ) {
			cout << temp << " ";
			for ( auto pot : pots ) {
				pots.insert(pot + temp);
				if ( pot + temp == C ) {
					right = true;
					goto end;
				}

			}
			
		}

end:
		cout << i+1 << " " << ( right ? "YES" : "NO" ) << "\n";

		pots.clear();

	}


}