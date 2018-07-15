#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const double PI = 3.1415926535897;

long long w, h, a;
double X1, Y1, X2, Y2, X3, Y3, X4, Y4;

int main()
{
	scanf("%lld%lld%lld", &w, &h, &a);
	if (w < h) swap(w, h);
	if (a > 90) a = 180 - a;
	if (a == 0) { printf("%.9lf\n", w * 1.0 * h); return 0; }
	if (a == 90) { printf("%.9lf\n", h * 1.0 * h); return 0; }
	X1 = w / 2.0, Y1 = h / 2.0, X2 = -X1, Y2 = Y1;
	double s = sin(a / 180.0 * PI), c = cos(a / 180.0 * PI);
	X3 = X1 * c - Y1 * s;
	Y3 = X1 * s + Y1 * c;
	X4 = X2 * c - Y2 * s;
	Y4 = X2 * s + Y2 * c;
	if (a >= atan(h * 1.0 / w) / PI * 180.0 * 2)
		printf("%.9lf\n", h / s * h);
	else
	{
		double k = (Y3 - Y4) / (X3 - X4), b = Y3 - k * X3;
		double t = (h / 2.0 - b) / k + w / 2.0, s = w - t - t / c;
		printf("%.9lf\n", w * h - t * t * tan(a / 180.0 * PI) - s * s / tan(a / 180.0 * PI));
	}
	return 0;
}
