#include <stdio.h>

#define MAX_PROB 10000
#define MAX_N	25
typedef unsigned long DWORD;

/* From
NEW VARIATIONS ON THE TOWER OF HANOI
by PAUL K. STOCKMEYER AND FRED LUNNON

  procedure Turtle(n)
  {
	stack = 0;
	Move(1, 0, 0, 1);
	for i from 1 to n-1 do
		stack = 1-stack;
		Move(i, stack, 2*stack, 2*stack+2);
		Hanoi(i-1, 1, stack, 2*stack+1, 2*stack, 2*stack+2);
		Move(i+1, stack, 2*stack, 2*stack+1);
		Hanoi(i, 1, stack, 2*stack+2, 2*stack, 2*stack+1);

    stack = 1-stack;
	Move(n, stack, 2*stack, 2*stack+2);

    for i from n-1 down to 1 do
		stack = 1-stack;
		Hanoi(i, 1, stack, 2*stack+1, 2*stack+2, 2*stack);
		Move(i+1, stack, 2*stack+1, 2*stack+2);
		Hanoi(i-1, 1, stack, 2*stack, 2*stack+2, 2*stack+1);
		Move(i, stack, 2*stack, 2*stack+2);

    stack = 1-stack;
	Move(1, 0, 1, 2);
  }

  this has white at 0 moving to 2 using 1 and black at 2 moving to 0 using 3
  stack = 0 is white stack = 1 is black
  so we need label lookups

  Move(level, color, from, to) moves one bldg of given level and color from location from to to
  Hanoi(largest, smallest, color, from, temp, to) moves the stack from largest to smallest
	from location from to location to using location temp for temporary storage

  procedure Hanoi(bottom, top, stack, from, via, to)
	if(top<=bottom)
		Hanoi(bottom-1, top, stack, from, to, via);
		Move(bottom, stack, from, to);
		Hanoi(bottom-1, top, stack, via, from, to);

  Hanoi(bottom, top) takes 2^(bottom - top + 1) - 1 moves

  in the first loop pass i takes 1 + (2^(i-1) - 1) + 1 + (2^i - 1) = 3*(2^(i-1)) moves
  the sum of all passes is 3*(2^(n-1) - 1)

  in the second loop pass i takes the sam number of moves + 3 single top level moves
  for a total of 3*(2^n -1) moves
*/

char *label[2] = {"white", "black"};
int lot[4] = {1, 2, 3, 4};

DWORD HanoiCnt[26];
DWORD Pass1Cnt[26];
DWORD Pass1CumCnt[26];
DWORD Pass2CumCnt[26];
DWORD SolnCnt[25];

void MakeCnts()
{
	int i;
	DWORD val;
	Pass1CumCnt[0] = HanoiCnt[0] = 0;
	for(i = 1, val = 1; i <= 25; i++, val *= 2) {
		HanoiCnt[i] = 2*val -1;
		SolnCnt[i] = 3*HanoiCnt[i];
		Pass1Cnt[i] = 3*val;
		Pass1CumCnt[i] = Pass1CumCnt[i-1] + Pass1Cnt[i];
	}
}

void PrintMove(int probnum, int n, int level, int color, int from, int to)
{
	printf("%d %ld MOVE %s FLOOR FROM LOT %d to LOT %d\n",
		probnum, SolnCnt[n], label[color], lot[from & 3], lot[to & 3]);
}

int PrintHanoi(int probnum, int n, DWORD move, int levels, int color, int from, int via, int to)
{
	if((move <= 0) || (move > HanoiCnt[levels])) {
		return -1;
	}
	if(move <= HanoiCnt[levels-1]) {
		return PrintHanoi(probnum, n, move, levels-1, color, from, to, via);
	} else {
		move -= HanoiCnt[levels-1];
		if(move == 1) {
			PrintMove(probnum, n, levels, color, from, to);
			return 0;
		} else {
			move--;
			return PrintHanoi(probnum, n, move, levels-1, color, via, from, to);
		}
	}
}

int PrintTurtle(int probnum, int n, DWORD move)
{
	int stack, i;
	if((move <= 0) || (move > SolnCnt[n])) {
		return -1;
	}
	stack = 0;
	if(move == 1) {
		PrintMove(probnum, n, 1, 0, 0, 1);
		return 0;
	}
	if(move == SolnCnt[n]) {
		PrintMove(probnum, n, 1, 0, 1, 2);
		return 0;
	}
	move--;
	if(move <= Pass1CumCnt[n-1]) {
		for(i = 1; i <= n-1; i++) {
			stack = 1-stack;
			if(move <= Pass1Cnt[i]) {
				if(move == 1) {
					PrintMove(probnum, n, i, stack, 2*stack, 2*stack+2);
					return 0;
				}
				move --;
				if(move <= HanoiCnt[i-1]) {
					return PrintHanoi(probnum, n, move, i-1, stack, 2*stack+1, 2*stack, 2*stack+2);
				}
				move -= HanoiCnt[i-1];
				if(move == 1) {
					PrintMove(probnum, n, i+1, stack, 2*stack, 2*stack+1);
					return 0;
				}
				move --;
				return PrintHanoi(probnum, n, move, i, stack, 2*stack+2, 2*stack, 2*stack+1);
			} else {
				move -= Pass1Cnt[i];
			}
		}
		return -2;	// should not get here
	} else {
		stack = n & 1;
		move -= Pass1CumCnt[n-1];
	}

	if(move == 1) {
		PrintMove(probnum, n, n, stack, 2*stack, 2*stack+2);
		return 0;
	}
	move --;
    for(i = n-1; i >= 1 ; i--){
		stack = 1-stack;
		if(move <= Pass1Cnt[i]) {
			if(move <= HanoiCnt[i]) {
				return PrintHanoi(probnum, n, move, i, stack, 2*stack+1, 2*stack+2, 2*stack);
			} else {
				move -= HanoiCnt[i];
			}
			if(move == 1) {
				PrintMove(probnum, n, i+1, stack, 2*stack+1, 2*stack+2);
				return 0;
			}
			move --;
			if(move <= HanoiCnt[i-1]) {
				return PrintHanoi(probnum, n, move, i-1, stack, 2*stack, 2*stack+2, 2*stack+1);
			}
			move -= HanoiCnt[i-1];
			if(move != 1) {
				return -3;
			}
			PrintMove(probnum, n, i, stack, 2*stack, 2*stack+2);
			return 0;
		} else {
			move -= Pass1Cnt[i];
		}
	}
	return -4;
}

char inbuf[256];
int main()
{
	int nprob, curprob, index, ret, n;
	DWORD move;

	if(fgets(&(inbuf[0]), 255, stdin) == NULL)
	{
		fprintf(stderr, "Read failed on problem count\n");
		return -1;
	}
	if(sscanf(&(inbuf[0]), "%d", &nprob) != 1)
	{
		fprintf(stderr, "Scan failed on problem count\n");
		return -2;
	}
	if((nprob < 1) || (nprob > MAX_PROB)) {
		fprintf(stderr, "problem count %d not in range 1 ...%d\n", nprob, MAX_PROB);
		return -3;
	}
	MakeCnts();
	for(curprob = 1; curprob <= nprob ; curprob++)
	{
		if(fgets(&(inbuf[0]), 255, stdin) == NULL)
		{
			fprintf(stderr, "Read failed on problem %d data\n", curprob);
			return -4;
		}
		if(sscanf(&(inbuf[0]), "%d %d %lu", &index, &n, &move) != 3) {
			fprintf(stderr, "scan failed on problem %d data\n", curprob);
			return -5;
		}
		if(index != curprob) {
			fprintf(stderr, "problem index %d not = expected problem %d\n",
				index, curprob);
			return -6;
		}
		if((n < 1) || (n > MAX_N) || (move < 1) || (move > SolnCnt[n])) {
			fprintf(stderr, "bad value of n %d and/or move %lu  problem %d\n",
				n, move, curprob);
			return -7;
		}
		if((ret = PrintTurtle(curprob, n, move)) < 0) {
			return ret - 10;
		}
	}
	return 0;
}