#include <iostream>
#include <cmath>

using namespace std;

double dist(int a1, int a2, int b1, int b2) {
        return pow(a1-b1, 2) + pow(a2-b2, 2);
}

double angle(double a, double b, double c) {
        return acos((a - b - c)/(-2*sqrt(b*c)));
}

int main()
{
        int a1, a2, b1, b2, c1, c2;

        cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2;

        // ab
        int ab = dist(a1, a2, b1, b2);

        // ac
        int ac = dist(a1, a2, c1, c2);

        // bc
        int bc = dist(b1, b2, c1, c2);

        double A = angle(bc, ab, ac);
        double B = angle(ac, ab, bc);
        double C = angle(ab, ac, bc);

        if (A >= M_PI*120/180) {
                cout << a1 << " " << a2 << endl;
                return 0;
        } else if (B >= M_PI*120/180) {
                cout << b1 << " " << b2 << endl;
                return 0;
        } else if (C >= M_PI*120/180) {
                cout << c1 << " " << c2 << endl;
                return 0;
        }

        // triliniar coordinates
        double otd = 60*M_PI/180;
        double x = 1/(sin(A + otd)/M_PI*180);
        double y = 1/(sin(B + otd)/M_PI*180);
        double z = 1/(sin(C + otd)/M_PI*180);

        double A1 = a1-c1,
                A2 = a2-c2,
                B1 = b1-c1,
                B2 = b2-c2;

        double a = sqrt(bc), b = sqrt(ac), c = sqrt(ab);

        double resx = a*x/(a*x+b*y+c*z)*A1 + b*y/(a*x+b*y+c*z)*B1;
        double resy = a*x/(a*x+b*y+c*z)*A2 + b*y/(a*x+b*y+c*z)*B2;

        printf("%.9lf %.9lf\n", c1+resx, c2+resy);

        return 0;
}