#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
        int k, y, x;

        cin >> x >> y >> k;

        int totalVertical = 0;
        double totalHorizontal = 0;

        for (int i = 0; i < k; ++i) {
                int l, u;
                double f;
                cin >> l >> u >> f;

                totalVertical += u-l;
                totalHorizontal += (u-l)*f;
        }

        totalHorizontal += y-totalVertical;

        printf("%.10lf\n", ((double)x)/totalHorizontal);

        return 0;
}