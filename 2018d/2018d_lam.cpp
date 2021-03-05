#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

struct v3 {
	double x, y, z;

	v3() {}

	v3(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	double abs() {
		return sqrt(x*x + y*y + z*z);
	}

	double dot(v3 other) {
		return x*other.x + y*other.y + z*other.z;
	}

	v3 normalize() {
		return times(1/abs());
	}

	v3 proj(v3 other) {
		return other.times(dot(other) / other.dot(other));
	}

	v3 times(double scalar) {
		return v3{scalar*x, scalar*y, scalar*z};
	}

	v3 add(v3 other) {
		return v3{x+other.x, y+other.y, z+other.z};
	}

	v3 subtract(v3 other) {
		return add(other.times(-1));
	}
	
	v3 cross(v3 other) {
		return v3{
			y*other.z - z*other.y,
			-(x*other.z - z*other.x),
			x*other.y - y*other.x
		};
	}
};

int main(void)
{
	int P, K, i;

	cin >> P;

	for (i = 0; i < P; ++i) {
		double RT, RP, OFF, SLP;
		cin >> K >> RT >> RP >> OFF >> SLP;

		v3 off = v3{OFF, 0, 0};
		v3 d = v3{0, 1, SLP};
		v3 v1 = v3{1, 0, 0}.times(RP);
		v3 v2 = d.cross(v1).normalize().times(RP);
		double rt2 = RT*RT;

		// go around the circle
		double th, t, inc = 1e-3, dist = 0;
		v3 bp, pp, first, last;
		for (th = 0; th < 2*M_PI; th += inc) {
			// calculate "base point" on "base circle"
			bp = off.add(v1.times(sin(th))).add(v2.times(cos(th)));

			// calculate t
			t = -bp.y + sqrt(rt2 - pow(bp.x, 2));

			// calculate projected point
			pp = bp.add(d.times(t));

			// calculate distance
			if (th)
				dist += pp.subtract(last).abs();
			else
				first = pp;
			last = pp;
		}

		dist += last.subtract(first).abs();
		printf("%d %0.3f\n", K, dist);
	}
}