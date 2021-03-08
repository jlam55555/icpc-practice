#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <stack>
#include <cctype>
#include <unordered_map>
#include <unordered_set>

#define DEBUG 0

using namespace std;

enum opcode {
	PUSHPOS, PUSHNEG,
	DUP, SWAP, DISCARD,
	ADD, SUB, MUL, DIV, MOD,
	STORE, LOAD, OUTDEC,
	OUTC, READC, READINT,
	LABEL, CALL, JMP, JMPZ, JMPL,
	RET, EXIT, INVAL=-1, INEOF=-2
};

// for debugging purposes
string op2str(enum opcode op) {
	switch(op) {
	case PUSHPOS:	return "PUSHPOS";
	case PUSHNEG:	return "PUSHNEG";
	case DUP:	return "DUP";
	case SWAP:	return "SWAP";
	case DISCARD:	return "DISCARD";
	case ADD:	return "ADD";
	case SUB:	return "SUB";
	case MUL:	return "MUL";
	case DIV:	return "DIV";
	case MOD:	return "MOD";
	case STORE:	return "STORE";
	case LOAD:	return "LOAD";
	case OUTDEC:	return "OUTDEC";
	case OUTC:	return "OUTC";
	case READC:	return "READC";
	case READINT:	return "READINT";
	case LABEL:	return "LABEL";
	case CALL:	return "CALL";
	case JMP:	return "JMP";
	case JMPZ:	return "JMPZ";
	case JMPL:	return "JMPL";
	case RET:	return "RET";
	case EXIT:	return "EXIT";
	}
	return "";
}

enum opcode parse(string &, int &);
int readNumber(string &, int &);
string readLabel(string &, int &);

int readInNumber(string &, int &);
char readInChar(string &, int &);

unordered_set<int> rtErrPos{};

stack<int> stk{};
stack<int> fnStk{};
void progExit() {
	exit(0);
}
void progExitErr() {
	cout << "RUN-TIME ERROR" << endl;
	exit(0);
}
unordered_map<int, int> heap{};
unordered_map<string, int> labels{};
void stackPush(int val) {
	if (stk.size() == 1024) {
		progExitErr();
	}

	stk.push(val);
}
int stackPop() {
	if (stk.empty()) {
		progExitErr();
	}

	int val = stk.top();
	stk.pop();
	return val;
}
int stackTop() {
	if (stk.empty()) {
		progExitErr();
	}

	return stk.top();
}
void heapStore(int to, int val) {
	heap[to] = val;
}
int heapLoad(int from) {
	if (heap.count(from) == 0) {
		return 0;
	}

	return heap[from];
}
// this is done both at preprocessing and runtime
void labelSet(string label, int pos, bool isRunTime) {
	if (!isRunTime && labels.count(label)) {
		rtErrPos.insert(pos);
	} else if (isRunTime && rtErrPos.count(pos)) {
		progExitErr();
	}

	labels[label] = pos;
}
int labelGet(string label) {
	if (!labels.count(label)) {
		progExitErr();
	}

	return labels[label];
}
void fnCall(int pos) {
	if (fnStk.size() == 1024) {
		progExitErr();
	}

	fnStk.push(pos);
}
int fnRet() {
	if (fnStk.empty()) {
		progExitErr();
	}

	int val = fnStk.top();
	fnStk.pop();
	return val;
}

void installLabels(string &s)
{
	int pos = 0;
	enum opcode parseRet;
	string label;

	#if DEBUG
	cout << "PREPROCESSING STAGE" << endl;
	#endif
	while ((parseRet = parse(s, pos)) != INEOF) {
		if (parseRet < 0) {
			// syntax error, will be picked up at runtime
			goto done;
		}

		#if DEBUG
		cout << "OPCODE: " << op2str(parseRet) << endl;
		#endif

		switch(parseRet) {
		case PUSHPOS:
		case PUSHNEG:
			readNumber(s, pos);
			break;
		case LABEL:
			label = readLabel(s, pos);
			labelSet(label, pos, false);
			break;
		case CALL:
		case JMP:
		case JMPZ:
		case JMPL:
			label = readLabel(s, pos);
			break;
		case EXIT:
			goto done;
		}
	}

done:;
	#if DEBUG
	cout << "END PREPROCESSING STAGE" << endl;
	#endif
}

void processLine(string &s, int &pos, string &in, int &inPos)
{
	#if DEBUG
	cout << "pos=" << pos;
	#endif

	enum opcode parseRet = parse(s, pos);
	int s1, s2;
	string label;
	if (parseRet == INEOF) {
		progExit();
	} else if (parseRet < 0) {
		progExitErr();
	}

	#if DEBUG
	cout << " code=" << op2str(parseRet) << endl;
	#endif

	switch(parseRet) {
	case PUSHPOS:
		stackPush(readNumber(s, pos));
		break;
	case PUSHNEG:
		stackPush(-readNumber(s, pos));
		break;
	case DUP:
		stackPush(stackTop());
		break;
	case SWAP:
		s1 = stackPop();
		s2 = stackPop();
		stackPush(s1);
		stackPush(s2);
		break;
	case DISCARD:
		stackPop();
		break;
	case ADD:
		s1 = stackPop();
		s2 = stackPop();
		stackPush(s1 + s2);
		break;
	case SUB:
		s1 = stackPop();
		s2 = stackPop();
		stackPush(s2 - s1);
		break;
	case MUL:
		s1 = stackPop();
		s2 = stackPop();
		stackPush(s1 * s2);
		break;
	case DIV:
		s1 = stackPop();
		s2 = stackPop();
		stackPush(s2 / s1);
		break;
	case MOD:
		s1 = stackPop();
		s2 = stackPop();
		stackPush(s2 % s1);
		break;
	case STORE:
		s1 = stackPop();
		s2 = stackPop();
		heapStore(s2, s1);
		break;
	case LOAD:
		s1 = stackPop();
		stackPush(heapLoad(s1));
		break;
	case LABEL:
		label = readLabel(s, pos);
		// LABELS INSTALLED IN PREPROCESSING STAGE
		labelSet(label, pos, true);
		break;
	case CALL:
		label = readLabel(s, pos);
		fnCall(pos);
		break;
	case JMP:
		label = readLabel(s, pos);
		pos = labelGet(label);
		break;
	case JMPZ:
		label = readLabel(s, pos);
		s1 = stackPop();
		if (!s1) {
			pos = labelGet(label);
		}
		break;
	case JMPL:
		label = readLabel(s, pos);
		s1 = stackPop();
		if (s1 < 0) {
			pos = labelGet(label);
		}
		break;
	case RET:
		pos = fnRet();
		break;
	case EXIT:
		progExit();
		break;
	case OUTC:
		s1 = stackPop();
		printf("%c", s1);
		break;
	case OUTDEC:
		s1 = stackPop();
		printf("%d", s1);
		break;
	case READC:
		char c;
		s1 = stackPop();
		c = readInChar(in, inPos);
		heapStore(s1, c);
		break;
	case READINT:
		int dec;
		s1 = stackPop();
		dec = readInNumber(in, inPos);
		heapStore(s1, dec);
		break;
	}
}

enum opcode parse(string &s, int &pos)
{
	int i = pos;
	int a, b, c, d;

	if (i == s.length()) {
		return INEOF;
	}

	a = s[i]-'0';
	b = i < s.length()-1 ? (s[i+1]-'0') : -1;
	c = i < s.length()-2 ? (s[i+2]-'0') : -1;
	d = i < s.length()-3 ? (s[i+3]-'0') : -1;

	if (a == 0) {
		if (b == 0) {
			if (c == 0) {
				pos += 3;
				return PUSHPOS;
			} else if (c == 1) {
				pos += 3;
				return PUSHNEG;
			}
			return INVAL;
		} else if (b == 2) {
			if (c == 0) {
				pos += 3;
				return DUP;
			} else if (c == 1) {
				pos += 3;
				return SWAP;
			} else {
				pos += 3;
				return DISCARD;
			}
		}
		return INVAL;
	} else if (a == 1) {
		if (b == 0) {
			if (c == 0) {
				if (d == 0) {
					pos += 4;
					return ADD;
				} else if (d == 1) {
					pos += 4;
					return SUB;
				} else if (d == 2) {
					pos += 4;
					return MUL;
				}
			} else if (c == 1) {
				if (d == 0) {
					pos += 4;
					return DIV;
				} else if (d == 1) {
					pos += 4;
					return MOD;
				}
				return INVAL;
			}
			return INVAL;
		} else if (b == 1) {
			if (c == 0) {
				pos += 3;
				return STORE;
			} else if (c == 1) {
				pos += 3;
				return LOAD;
			}
			return INVAL;
		} else if (b == 2) {
			if (c == 0) {
				if (d == 0) {
					pos += 4;
					return OUTC;
				} else if (d == 1) {
					pos += 4;
					return OUTDEC;
				}
				return INVAL;
			} else if (c == 1) {
				if (d == 0) {
					pos += 4;
					return READC;
				} else if (d == 1) {
					pos += 4;
					return READINT;
				}
				return INVAL;
			}
			return INVAL;
		}
	} else if (a == 2) {
		if (b == 0) {
			if (c == 0) {
				pos += 3;
				return LABEL;
			} else if (c == 1) {
				pos += 3;
				return CALL;
			} else {
				pos += 3;
				return JMP;
			}
		} else if (b == 1) {
			if (c == 0) {
				pos += 3;
				return JMPZ;
			} else if (c == 1) {
				pos += 3;
				return JMPL;
			} else {
				pos += 3;
				return RET;
			}
		} else if (b == 2) {
			if (c == 2) {
				pos += 3;
				return EXIT;
			}
			return INVAL;
		}
	}

	return INVAL;
}

int readNumber(string &s, int &pos)
{
	int curPos = pos, res;
	while (s[curPos] != '2') {
		++curPos;
	}
	res = stoi(s.substr(pos, curPos-pos+1), nullptr, 2);
	pos = curPos+1;
	return res;
}

char readInChar(string &in, int &pos)
{
	char c = in[pos];
	++pos;
	return c;
}

int readInNumber(string &in, int &pos)
{
	int res = 0, sign = 1;
	if (in[pos] == '+' || in[pos] == '-') {
		sign = in[pos] == '+' ? 1 : -1;
		++pos;
	}
	while (isdigit(in[pos])) {
		res = res*10 + (in[pos]-'0');
		++pos;
	}
	return res*sign;
}

string readLabel(string &s, int &pos) 
{
	int curPos = pos;
	string res;
	while (s[curPos] != '2') {
		++curPos;
	}
	res = s.substr(pos, curPos-pos+1);
	pos = curPos+1;
	return res;
}

int main()
{
	string s;
	int pos = 0;

	// read main program opcodes
	cin >> s;

	// read extra input
	string in, line;
	while (cin >> line) {
		in += line;
	}
	int inPos = 0;

	// preprocessing step: install labels since we can jump forward
	// (also detects label duplicates but this is only reported if
	// we reach one of these positions)
	installLabels(s);

	// regular parsing
	while (1) {
		processLine(s, pos, in, inPos);
	}
}