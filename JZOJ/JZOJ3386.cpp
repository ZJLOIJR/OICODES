#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2e2 + 7, M = 400;

int n, l, m;
int a[N];
double ans, prob[N], f[2][N << 2][N];

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	scanf("%d%d%d", &n, &l, &m);
	m = min(m, 200);
	for (int i = 1; i <= n; i++) scanf("%lf", prob + i), prob[i] /= 100;
	for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i] = min(a[i], 200);
	f[0][m + M][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = -200; j <= 200; j++)
		{
			f[i & 1][j + M][0] = f[(i - 1) & 1][j + M][0] * (1 - prob[i]);
			for (int k = 1; k <= i; k++)
				f[i & 1][j + M][k] = f[(i - 1) & 1][j + M][k] * (1 - prob[i]) + f[(i - 1) & 1][j - a[i] + M][k - 1] * prob[i];
		}
	for (int j = 0; j <= 200; j++)
		for (int k = l; k <= n; k++)
			ans += f[n & 1][j + M][k];
	printf("%.6lf\n", ans);
	return 0;
}
