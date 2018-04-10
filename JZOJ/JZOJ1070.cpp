#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

int n, m;
double f[21][21];

int main()
{
	scanf("%d%d", &n, &m);
	f[0][0] = 1.0;
	for (int i = 1; i <= m; i++)
		for (int j = 0; j <= n && j <= i; j++)
		{
			f[i][j] += f[i - 1][j] * (j * 1.0 / n);
			if (j) f[i][j] += f[i - 1][j - 1] * ((n - j + 1) * 1.0 / n);
		}
	printf("%.4lf\n", f[m][n]);
	return 0;
}
