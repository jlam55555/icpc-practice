/*
 * Tanks and Pipes
 * 2018 GNY Regional
 * by Fred Pickel, C-Scape Consulting Corp.
 */
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define EPS (0.0003)
double r1, r2, x, dz;
double pie = 3.14159265358979323846; 
/*
 * The idea is to find successivw points along the joint by intersecting a ray
 * in the pipe wall (parallel to the axis and r2 away) with the tank wall x^2 + y^2 = r1^2
 * the vector v1 = <1.0,0> is perpendicular to the pipe axis vector <0, 1, dz> as is <0, -dz, 1>
 * we make that unit vaector by dividing by sqrt(dz*dz + 1) to get v2
 * so now a point on the surface of the pipe is p = (px, py, pz) = (x, 0, 0) + r2*sin(theta)*v1 + r2*cos(theta)*v2
 * and the equation of the ray is p + t*<0, 1, dz>
 * substituting into the tank equation (px *px) + (py + t)*(py + t) = r1*r1
 * t^2 + 2*t*py + px*px + py*py - r1*r1 = 0
 * t = -py +- sqrt(py*py - px*px - py*py + r1*r1) = -py +- sqrt(r1*r1 - px*px)
 * substitute into p + t*<0, 1, dz> to get a point (x,y,z) on the joint
 * approximate thelength of the joint by adding up the distances between the points a theta goes around the circle
 * if the tank is flat the equaton is y = 0, so t = -py
 *
 * accelerating convergence
 * for a single sector of a circle for angle t, the length of the circle arc is r*t and the length of
 * chord is 2*r*sin(t/2) ~ 2*r*((t/2) - ((t/2)^3)/6) (power series for sin()
 * so the difference between chord length and arc length is 2*r*((t/2)^3)/6 = (r*t^3)/24
 * if we take twice as many steps (approximating the arc by 2 chords with angle (t/2)
 * the length of the 2 chords is 4*r*sin(t/4) ~ 4*r*(t/4 - ((t/4)^3)/6)
 * and the error is 4*r*((t/4)^3)/6 = (r*t^3)/96 = 1/4 of the error with half as many steps
 * so if len is the sum of the lengths of the hcords using N pts  and len2 is the sum using 2*N points
 * and lenT is the true lenghts we expect the (lenT - len2) ~ (1/4)(lenT - len)
 * sovling for lenT ~ (4*len2 - len)/3
 */
double v2[3];
double p[3];

void MakeV2()
{
	double mag = dz*dz + 1.0;
	mag = 1.0/sqrt(mag);
	v2[0] = 0.0;
	v2[1] = -dz*mag;
	v2[2] = mag;
}

int GetPtRnd(double theta, double *pPt)
{
	double t, c = r2*cos(theta);
	p[0] = x + r2*sin(theta);
	p[1] = c*v2[1];
	p[2] = c*v2[2];
	t = r1*r1 - p[0]*p[0];
	if(t < 0.0) return -1;
	t = -p[1] + sqrt(t);
	pPt[0] = p[0];
	pPt[1] = p[1] + t;
	pPt[2] = p[2] + t*dz;
	return 0;
}

int GetPtFlat(double theta, double *pPt)
{
	double t, c = r2*cos(theta);
	p[0] = x + r2*sin(theta);
	p[1] = c*v2[1];
	p[2] = c*v2[2];
	t = -p[1];
	pPt[0] = p[0];
	pPt[1] = p[1] + t;
	pPt[2] = p[2] + t*dz;
	return 0;
}

double pts[129][3];

double FindLength()
{
	double theta, dtheta, len1, len2, len3, len4,  dlen, dx, dy, dz, lenest, lenest2, lenest3;
	int i;
	MakeV2();
	dtheta = pie/8.0;
	theta = 0.0;
	for(i = 0; i < 128 ; i += 8, theta += dtheta) {
		if(r1 <= 0.0) {
			GetPtFlat(theta, &(pts[i][0]));
		} else {
			GetPtRnd(theta, &(pts[i][0]));
		}
	}
	pts[128][0] = pts[0][0];
	pts[128][1] = pts[0][1];
	pts[128][2] = pts[0][2];
	for(i = 0, len1 = 0.0; i < 128 ; i += 8) {
		dx = pts[i+8][0] - pts[i][0];
		dy = pts[i+8][1] - pts[i][1];
		dz = pts[i+8][2] - pts[i][2];
		dlen = dx*dx + dy*dy + dz*dz;
		len1 += sqrt(dlen);
	}
	theta = 0.5*dtheta;
	for(i = 4; i < 128 ; i += 8, theta += dtheta) {
		if(r1 <= 0.0) {
			GetPtFlat(theta, &(pts[i][0]));
		} else {
			GetPtRnd(theta, &(pts[i][0]));
		}
	}
	for(i = 0, len2 = 0.0; i < 128 ; i += 4) {
		dx = pts[i+4][0] - pts[i][0];
		dy = pts[i+4][1] - pts[i][1];
		dz = pts[i+4][2] - pts[i][2];
		dlen = dx*dx + dy*dy + dz*dz;
		len2 += sqrt(dlen);
	}
	lenest = (4.0*len2 - len1)/3.0;
	dtheta *= 0.5;
	theta = 0.5*dtheta;
	for(i = 2; i < 128 ; i += 4, theta += dtheta) {
		if(r1 <= 0.0) {
			GetPtFlat(theta, &(pts[i][0]));
		} else {
			GetPtRnd(theta, &(pts[i][0]));
		}
	}
	for(i = 0, len3 = 0.0; i < 128 ; i+= 2) {
		dx = pts[i+2][0] - pts[i][0];
		dy = pts[i+2][1] - pts[i][1];
		dz = pts[i+2][2] - pts[i][2];
		dlen = dx*dx + dy*dy + dz*dz;
		len3 += sqrt(dlen);
	}
	lenest2 = (4.0*len3 - len2)/3.0;
	if(fabs(lenest2 - lenest) < EPS) {
		return lenest2;
	}
	dtheta *= 0.5;
	theta = 0.5*dtheta;
	for(i = 1; i < 128 ; i += 2, theta += dtheta) {
		if(r1 <= 0.0) {
			GetPtFlat(theta, &(pts[i][0]));
		} else {
			GetPtRnd(theta, &(pts[i][0]));
		}
	}
	for(i = 0, len4 = 0.0; i < 128 ; i++) {
		dx = pts[i+1][0] - pts[i][0];
		dy = pts[i+1][1] - pts[i][1];
		dz = pts[i+1][2] - pts[i][2];
		dlen = dx*dx + dy*dy + dz*dz;
		len4 += sqrt(dlen);
	}
	lenest3 = (4.0*len4 - len3)/3.0;
	if(fabs(lenest3 - lenest2) < EPS) {
		return lenest3;
	} else {
		printf("lens %.4lf %.4lf %.4lf %.4lf est %.4lf %.4lf %.4lf\n",
			len1, len2, len3, len4, lenest, lenest2, lenest3);
		return -1;
	}
}

char inbuf[256];
int main()
{
	int nprob, curprob, index;
	double ret;
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
	for(curprob = 1; curprob <= nprob ; curprob++)
	{
		if(fgets(&(inbuf[0]), 255, stdin) == NULL)
		{
			fprintf(stderr, "Read failed on problem %d \n", curprob);
			return -3;
		}
		if(sscanf(&(inbuf[0]), "%d %lf %lf %lf %lf", &index, &r1, &r2, &x, &dz) != 5) {
			fprintf(stderr, "scan failed on problem %d header\n", curprob);
			return -4;
		}
		if(index != curprob) {
			fprintf(stderr, "problem index %d not = expected problem %d\n",
				index, curprob);
			return -5;
		}
		if((r1 > 0.0) && ((r2 + x) > r1)) {
			fprintf(stderr, "pipe radius %lf + offset %lf > tank radius %lf\n",
				r2, x, r1);
			return -6;
		}
		if((ret = FindLength()) > 0.0) {
			printf("%d %.3lf\n", curprob, ret);
		}
	}
	return 0;
}