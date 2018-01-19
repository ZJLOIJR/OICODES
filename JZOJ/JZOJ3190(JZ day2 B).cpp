#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 107;

int n;
double x[N], y[N];
double ans = 666666666.0;

inline double sqr(double x)
{ return x * x; }
inline double getdis(double x1, double y1, double x2, double y2)
{ return sqrt(sqr(x1 - x2) + sqr(y1 - y2)); }
inline double min(double a, double b)
{ return a < b ? a : b; }

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", x + i, y + i);
	if (n < 3) { printf("Impossible\n"); return 0; }
	for (int i = 1; i <= n - 2; i++)
		for (int j = i + 1; j <= n - 1; j++)
			for (int k = j + 1; k <= n; k++)
			{
				double a = getdis(x[i], y[i], x[j], y[j]),
					   b = getdis(x[j], y[j], x[k], y[k]),
					   c = getdis(x[i], y[i], x[k], y[k]),
					   p = (a + b + c) / 2,
					   s = sqrt(p * (p - a) * (p - b) * (p - c));
				if (s > 0.01) ans = min(ans, s);
			}
	if (ans == 666666666.0) printf("Impossible\n");
	else printf("%.2lf\n", ans);
	return 0;
}
