#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
inline double sqr(double a) { return a * a; }
inline double dis(double xx, double yy, double x, double y) { return sqrt(sqr(xx - x) + sqr(yy - y)); }
inline double min(double a, double b) { return a < b ? a : b; }
inline double max(double a, double b) { return a > b ? a : b; }

const int N = 1e3 + 3;
const double PI = 3.1415926535;
int n, x[N], y[N];
double ans = 2333333333.0;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
	for (int i = 1; i <= n; i++)
	{
		double mxdis = 0;
		for (int j = 1; j <= n; j++)
			if (j != i) mxdis = max(mxdis, dis(x[i], y[i], x[j], y[j]));
		ans = min(ans, mxdis * mxdis * PI);
	}
	printf("%.4lf\n", ans);
	return 0;
}
