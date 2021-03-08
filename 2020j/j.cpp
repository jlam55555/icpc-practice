#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

int board[1001][1001] = {0};

int main()
{
	int nrows, ncols, y, x;

	// get number of datasets
	cin >> nrows >> ncols;

	int ca = 0, ica = 0;

	for (y = 0; y < nrows; ++y ) {
		for (x = 0; x < ncols; ++x) {
			cin >> board[y][x];
			// cout << board[y][x] << " ";
		}
		// cout << endl;
	}

	for (y = 0; y < nrows; ++y ) {
		for (x = 0; x < ncols; ++x) {
			if (board[y][x]) {
				if (x && y < nrows-1) {
					ica += board[y+1][x-1];
				}
				if (x < ncols-1 && y < nrows-1) {
					ica += board[y+1][x+1];
				}

				if (x < ncols - 1) {
					ca += board[y][x+1];
				}
				if (y < nrows-1) {
					ca += board[y+1][x];
				}
			}
		}
	}

	cout << ca << " " << (ca+ica) << endl;


	return 0;
}