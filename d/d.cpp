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

        if (ab > ac) {
                // c is center
                cout << (a1+b1-c1) << " " << (a2+b2-c2) << endl;
        } else if (ac > ab) {
                // b is center
                cout << (a1+c1-b1) << " " << (a2+c2-b2) << endl;
        } else if (bc > ab) {
                // a is center
                cout << (c1+b1-a1) << " " << (c2+b2-a2) << endl;
        }
}