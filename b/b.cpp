#include <iostream>

using namespace std;

int main()
{
        int D, R, T;

        cin >> D >> R >> T;

        for (int r = 3; ; ++r) {
                int n = r+D;

                if (n*(n+1)/2-6 + r*(r+1)/2-3 == R+T) {
                        cout << abs(n*(n+1)/2-6-R) << endl;
                        return 0;
                }
        }
}