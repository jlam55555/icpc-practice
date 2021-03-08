#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

struct vec2 {
	double x, y;

	vec2() {}

	vec2(double x, double y) {
		this->x = x;
		this->y = y;
	}

	double abs() {
		return sqrt(x*x + y*y);
	}

	double dot(vec2 other) {
		return x*other.x + y*other.y;
	}

	vec2 normalize() {
		return times(1/abs());
	}

	vec2 proj(vec2 other) {
		return other.times(dot(other) / other.dot(other));
	}

	vec2 times(double scalar) {
		return vec2{scalar*x, scalar*y};
	}

	vec2 add(vec2 other) {
		return vec2{x+other.x, y+other.y};
	}

	vec2 subtract(vec2 other) {
		return add(other.times(-1));
	}

	vec2 perp() {
		return vec2{-y, x};
	}

	vec2 reflect(vec2 start, vec2 dir) {
		vec2 sp = subtract(start);
		vec2 distToLine = sp.subtract(sp.proj(dir));
		return subtract(distToLine.times(2));
	}

	void print() {
		cout << "POINT " << x << " " << y << endl;
	}
};

struct line {
	vec2 start, dir;
	double length;

	line() {
		length = -1;
	}

	line(vec2 start, vec2 dir) {
		this->start = start;
		this->dir = dir;
		length = -1;
	}

	line(vec2 start, vec2 dir, double length) {
		this->start = start;
		this->dir = dir;
		this->length = length;
	}

	line(vec2 start, vec2 dir, bool calcLength) {
		this->start = start;
		this->dir = dir;
		this->length = dir.abs();
	}

	vec2 midpt() {
		if (length < 0) {
			printf("ERR LENGTH OF INFINITE LINE");
			return vec2{};
		}

		return start.add(dir.times(length/dir.abs()/2));
	}

	vec2 intersect(line other) {
		// construct matrix A
		double a = dir.x, b = -other.dir.x, c = dir.y, d = -other.dir.y;
		// construct matrix inverse
		double detA = a*d-b*c;
		double a2 = d/detA;
		double b2 = -b/detA;
		double c2 = -c/detA;
		double d2 = a/detA;
		// other points
		double spx = other.start.x - start.x;
		double spy = other.start.y - start.y;

		double t1 = a2*spx + b2*spy;
		double t2 = c2*spx + d2*spy;

		// find result point
		vec2 rp1 = start.add(dir.times(t1));
		vec2 rp2 = other.start.add(other.dir.times(t2));

		// cout << rp1.x << " " << rp2.x << " " << rp1.y << " " << rp2.y << endl;

		return rp1;
	}
};

struct tri {
	tri() { }

	vec2 a, b, c;
	line ab, ac, bc;

	tri(vec2 a, vec2 b, vec2 c) {
		this->a = a;
		this->b = b;
		this->c = c;
		ab = line{a, b.subtract(a), true};
		bc = line{b, c.subtract(b), true};
		ac = line{a, c.subtract(a), true};
	}

	double area() {
		// heron's formula
		double lab = ab.length, lbc = bc.length, lac = ac.length,
			p = (lab+lbc+lac)/2.;
		return sqrt(p*(p-lab)*(p-lbc)*(p-lac));
	}
};

int main()
{
	double bx, cx, cy;

	cin >> bx >> cx >> cy;

	vec2 a = vec2{0,0}, b = vec2{bx, 0}, c = vec2{cx, cy};
	tri t1{a, b, c};

	// find altitudes
	// altitude of A is perp to bc and goes through A
	line alta = line{a, t1.bc.dir.perp()},
		altb = line{b, t1.ac.dir.perp()},
		altc = line{c, t1.ab.dir.perp()};

	// find perpendicular bisectors
	line pba = line{t1.bc.midpt(), t1.bc.dir.perp()},
		pbb = line{t1.ac.midpt(), t1.ac.dir.perp()},
		pbc = line{t1.ab.midpt(), t1.ab.dir.perp()};

	// find intersections
	vec2 ap = altc.intersect(pbb),
		bp = alta.intersect(pbc),
		cp = altb.intersect(pba);

	tri t2{ap, bp, cp};

	// find triangle 3
	vec2 app = ap.reflect(t1.ac.start, t1.ac.dir),
		bpp = bp.reflect(t1.ab.start, t1.ab.dir),
		cpp = cp.reflect(t1.bc.start, t1.bc.dir);

	tri t3{app, bpp, cpp};

	printf("%0.4f %0.4f %0.4f\n", t1.area(), t2.area(), t3.area());

	return 0;
}