#include <cstdio>

int n, m;
double ans = 0.0, a[21], f[21][21];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lf", a + i);
	f[0][0] = 1.0;
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = f[i - 1][0] * (1 - a[i]);
		for (int j = 1; j <= i; j++)
			f[i][j] = f[i - 1][j - 1] * a[i] + f[i - 1][j] * (1 - a[i]);
	}
	for (int i = m; i <= n; i++) ans += f[n][i];
	printf("%.6lf\n", ans);
	return 0;
}
