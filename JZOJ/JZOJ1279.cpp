#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 3e2 + 3, M = 1e4 + 3;

int m, n, ans = 0x3f3f3f3f;
int a[N], b[N], f[N][M];

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	memset(f, 0x3f, sizeof(f));
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);
	f[1][0] = 1;
	for (int i = 1; i <= n + 1; i++)
		for (int j = 0; j <= m; j++)
		{
			if (f[i][j] >= 0x3f3f3f3f) continue;
			int suma = 0, sumb = 0;
			for (int k = i; k <= n + 1; k++)
			{
				f[k][m - sumb] = min(f[k][m - sumb], f[i][j] + 1);
				suma += a[k], sumb += b[k];
				if (suma > j || sumb > m) break;
			}
		}
	for (int i = 0; i <= m; i++) ans = min(ans, f[n + 1][i]);
	printf("%d\n", ans);
	return 0;
}
