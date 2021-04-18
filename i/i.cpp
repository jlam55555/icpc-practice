#include <iostream>
#include <stack>
#include <queue>
#include <climits>
using namespace std;

class Square
{
public:
        int x, y;
        int dist = INT_MAX;
        int seen = 0;

        Square() {}

        Square(int x, int y) {
                this->x = x;
                this->y = y;
        }

        bool operator()(Square *a, Square *b) {
                return a->dist > b->dist;
        }
};

int main()
{
        int h, w;

        cin >> h >> w;

        Square *squares = new Square[h*w];
        int *t = new int[h*w];
        for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                        cin >> t[i*w + j];
                        squares[i*w + j].y = i;
                        squares[i*w + j].x = j;
                }
        }

        priority_queue<Square *, vector<Square *>, Square> pq;
        squares[0].dist = 0;

        pq.push(squares);
        while (!pq.empty()) {
                Square *s = pq.top();
                pq.pop();

                if (s->seen) {
                        continue;
                }
                s->seen = 1;
                int x = s->x, y = s->y, dist = s->dist;

                if (x==w-1 && y==h-1) {
                        cout << s->dist << endl;
                        return 0;
                }

                #define ADDCOND(COND, X1, Y1, X2, Y2) \
                if ((COND) && !squares[(Y2)*w + X2].seen \
                        && squares[(Y2)*w + X2].dist > \
                        max(dist, max(0, t[(Y2)*w + X2]-t[(Y1)*w + X1]))) { \
                        squares[(Y2)*w + X2].dist = max(dist, max(0, t[(Y2)*w + X2]-t[(Y1)*w + X1]));      \
                        pq.push(&squares[(Y2)*w + X2]); \
                }

                ADDCOND(x>0,    x, y, x-1, y)
                ADDCOND(x<w-1,  x, y, x+1, y)
                ADDCOND(y>0,    x, y, x, y-1)
                ADDCOND(y<h-1,  x, y, x, y+1)
        }
}