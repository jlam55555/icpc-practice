#include <iostream>

using namespace std;

int main()
{
        int k, i;
        char curr, prev;
        int count = 0;

        cin >> k;

        prev = -1;
        for (i = 0; i < k; ++i) {
                cin >> curr;

                count += curr == prev;
                prev = curr;
        }

        cout << count << endl;
        return 0;
}