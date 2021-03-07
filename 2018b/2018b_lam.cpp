#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>

using namespace std;

#define	SOLVE_DEBUG

#define	MAX_FLOOR	25
#define	MAX_INPUT	10000

/* This will keep track of all the moves for each possible case */
struct SMoveInfo {
	unsigned long m_dwWanted;
	string m_szMove;
};
unordered_map<int, string> wanted[MAX_FLOOR + 1];
unsigned long moves[MAX_FLOOR + 1];
unsigned long dwWantedMasks[MAX_FLOOR + 1][MAX_INPUT / 32];

#define	SET_WANTED(idx, n)	dwWantedMasks[idx][(n)/32] |= (1<<((n)&3)
#define	IS_WANTED(idx, n)	((dwWantedMasks[idx][(n)/32] & (1<<((n)&31))) != 0)

struct SInput {
	int m_nFloors;
	unsigned long m_dwMove;
};
SInput input_data[MAX_INPUT+1];
int nInput;

static const char *colors[2] = { "white", "black" };

unsigned long nMove, nDes;
int nCurrent;
char szAns[128];

void move(int d, int s, int f, int t)
{
	f &= 3;
	t &= 3;
#ifdef _DEBUGX
	printf("Move %s disk %d from %d to %d\n", colors[s], d, f, t);
#endif
	nMove++;
	if (wanted[nCurrent].find(nMove) != wanted[nCurrent].end()) {
		snprintf(&(szAns[0]), sizeof(szAns), "MOVE %s FLOOR FROM LOT %d to LOT %d",
			colors[s], f+1, t+1);
		wanted[nCurrent][nMove] = &(szAns[0]);
	}
	if(nMove == 0){
		printf("ooops\n");
	}
}

void hanoi(int b, int t, int s, int f, int u, int d)
{
	if(t <= b){
		hanoi(b-1, t, s, f, d, u);
		move(b, s, f, d);
		hanoi(b-1, t, s, u, f, d);
	}
}

void solve(int n)
{
	int s, i, s2;

	s = 0;
	move(1, 0, 0, 1);
	for(i = 1; i < n; i++){
		s = 1 - s;
		s2 = s + s;
		move(i, s, s2, s2+2);
		hanoi(i-1, 1, s, s2+1, s2, s2+2);
		move(i+1, s, s2, s2+1);
		hanoi(i, 1, s, s2+2, s2, s2+1);
	}
	s = 1 - s;
	s2 = s + s;
	move(n, s, s2, s2+2);
	for(i = n-1; i >= 1; i--){
		s = 1 - s;
		s2 = s + s;
		hanoi(i, 1, s, s2+1, s2+2, s2);
		move(i+1, s, s2+1, s2+2);
		hanoi(i-1, 1, s, s2, s2+2, s2+1);
		move(i, s, s2, s2+2);
	}
	s = 1-s;
	move(1, 0, 1, 2);
}

int main(int argc, char **argv)
{
	char ibuf[64];
	int p, k, i;
	SInput *pi;
	SMoveInfo mi;

	if(fgets(&(ibuf[0]), sizeof(ibuf)-1, stdin) != NULL){
		p = atoi(&(ibuf[0]));
		if (p > MAX_INPUT) {
			p = MAX_INPUT;
		}
		nInput = p;
		/* Gather all input and remember what we need in 'wanted', input itself is remembered in 'input_data' */
		for (k = 1; k <= p; k++) {
			if (fgets(&(ibuf[0]), sizeof(ibuf) - 1, stdin) == NULL) {
				break;
			}
			pi = &(input_data[k]);
			if (sscanf(&(ibuf[0]), "%d %d %lu", &(i), &(pi->m_nFloors), &(pi->m_dwMove)) != 3) {
				break;
			}
			wanted[pi->m_nFloors][pi->m_dwMove] = "No Move";
		}
		/* Solve for each case we need */
		for(k = 1; k <= MAX_FLOOR; k++){
			if (wanted[k].size() > 0) {
				nMove = 0;
				nCurrent = k;
				solve(k);
				moves[k] = nMove;
#ifdef SOLVE_DEBUG
				printf("%d floors, wanted %d moves, total moves:%lu\n", k, wanted[k].size(), nMove);
#endif
			}
		}
		/* Print results */
		for (k = 1; k <= p; k++) {
			pi = &(input_data[k]);
			nCurrent = pi->m_nFloors;
			printf("%d %lu %s\n", k, moves[nCurrent], wanted[pi->m_nFloors][pi->m_dwMove].c_str());
		}
	}
	return(0);
}