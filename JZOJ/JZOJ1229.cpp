#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e5 + 3, M = 12;

ll f[N][M];
int n, m, g[N][M];

int main()
{
	freopen("hanoi.in", "r", stdin);
	freopen("hanoi.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= 63; i++) f[i][3] = f[i - 1][3] * 2 + 1, g[i][3] = i - 1;
	for (int i = 1; i <= n; i++)
		for (int j = 4; j <= m; j++)
		{
			f[i][j] = (1LL << 61);
			int k1 = g[i - 1][j], k2 = g[i - 1][j] + 1;
			ll ret1 = f[i - k1][j - 1] + f[k1][j] * 2, ret2 = f[i - k2][j - 1] + f[k2][j] * 2;
			if (ret1 < f[i][j]) f[i][j] = ret1, g[i][j] = k1;
			if (ret2 < f[i][j]) f[i][j] = ret2, g[i][j] = k2;
		}
	printf("%lld\n", f[n][m]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
