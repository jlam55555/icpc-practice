#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int hints[10][10], board[10][10];

void print_board()
{
	int i, j;

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			if (hints[i][j] == -1) {
				switch (board[i][j]) {
				case 0: printf(" -  "); break;
				case 1: printf(" i  "); break;
				case 2: printf("ii  "); break;
				case 3: printf("iii "); break;
				}
			} else {
				printf("%3d ", hints[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

bool unsolved()
{
	int i, j;

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			if (hints[i][j] == -1 && !board[i][j]) {
				return true;
			}
		}
	}
	return false;
}

int solve()
{
	// until board is solved
	while (unsolved()) {
		print_board();
		break;
	}
	return 0;
}

int main(void)
{
	int P, K, i;

	cin >> P;

	for (i = 0; i < P; ++i) {
		cin >> K;

		memset(hints, 0, sizeof(hints));
		memset(board, 0, sizeof(hints));

		// inputting board
		int j, k;
		for (j = 0; j < 10; ++j) {
			for (k = 0; k < 10; ++k) {
				cin >> hints[j][k];
			}
		}

		// solve
		solve();
	}
}