#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define bit(x) (1 << ((x) - 1))
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, m, maxs, tot, ans;
int a[101], f[2][101][9][(1 << 8) + 1];

int main()
{
	tot = 0;
	while (1)
	{
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		++tot;
		memset(f, 0x3f, sizeof(f));
		maxs = 0, ans = 0x3f3f3f3f, f[0][0][0][0] = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", a + i);
			a[i] -= 24;
			maxs |= bit(a[i]);
		}
		for (int i = 0; i <= n - 1; i++)
		{
			int now = ((i + 1) & 1), las = (i & 1);
			memset(f[now], 0x3f, sizeof(f[now]));
			for (int j = 0; j <= m; j++)
				for (int k = 0; k <= 8; k++)
					for (int s = 0; s <= maxs; s++)
					{
						int tmp = f[las][j][k][s];
						if (tmp >= 0x3f3f3f3f) continue;
						if (j < m) f[now][j + 1][k][s] = min(f[now][j + 1][k][s], tmp);
						if (k != a[i + 1]) tmp++;
						f[now][j][a[i + 1]][s | bit(a[i + 1])] = min(f[now][j][a[i + 1]][s | bit(a[i + 1])], tmp);
					}
		}
		for (int j = 0; j <= m; j++)
			for (int k = 0; k <= 8; k++)
				for (int s = 0; s <= maxs; s++)
				{
					int nows = maxs - s, tmp = f[n & 1][j][k][s];
					while (nows > 0)
					{
						tmp += (nows & 1);
						nows >>= 1;
					}
					ans = min(ans, tmp);
				}
		printf("Case %d: %d\n\n", tot, ans);
	}
	return 0;
}

// 3853
