#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 7;
const double eps = 1e-8, INF = 1000000000.0;

int n;
double ans = INF, x[N], y[N];

double area(int a, int b, int c)
{
	double xx = x[b] - x[a], yy = y[b] - y[a], x_ = x[c] - x[a], y_ = y[c] - y[a];
	return fabs(xx * y_ - x_ * yy) / 2;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lf%lf", x + i, y + i);
	for (int i = 1; i <= n - 2; i++)
		for (int j = i + 1; j <= n - 1; j++)
			for (int k = j + 1; k <= n; k++)
				if (area(i, j, k) > eps && area(i, j, k) < ans) ans = area(i, j, k);
	if (ans == INF) printf("Impossible\n");
	else printf("%.2lf\n", ans);
	return 0;
}
