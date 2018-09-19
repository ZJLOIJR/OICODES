#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 57;

int T;
int n, x[N], y[N], r[N], X1, Y1, X2, Y2, u, v, ur = 2333, vr = 2333;
int t[N];

double sqr(double a) { return a * a; }
double getdis(double X1, double Y1, double X2, double Y2)
{
	return sqrt(sqr(X1 - X2) + sqr(Y1 - Y2));
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", x + i);
		for (int i = 1; i <= n; i++) scanf("%d", y + i);
		for (int i = 1; i <= n; i++) scanf("%d", r + i);
		for (int i = 1; i <= n; i++)
		{
			if (getdis(x[i], y[i], X1, Y1) <= r[i] && r[i] < ur) u = i, ur = r[i];
			if (getdis(x[i], y[i], X2, Y2) <= r[i] && r[i] < vr) v = i, vr = r[i];
		}
		for (int i = 1; i <= n; i++)
			if (getdis(x[i], y[i], x[u], y[u]) + r[u] <= r[i]) t[i] = 1;
	}
	return 0;
}
