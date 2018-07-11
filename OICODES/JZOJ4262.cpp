#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

const int N = 3e3 + 7;

int n, r;
int a[N], f[N][N], pre[N], suf[N], g[N][N], ans[N];

int main()
{
	n = read(), r = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	memset(f, -0x3f, sizeof(f));
	for (int i = 1; i <= n - 1; i++) f[0][i] = 0;
	for (int i = 1; i <= n; i++)
	{
		pre[1] = 1;
		for (int j = 2; j <= n - 1; j++)
		{
			if (f[i - 1][j] + a[(j - 1 - (i - 1) * r % n + n) % n + 1] > f[i - 1][pre[j - 1]] + a[(pre[j - 1] - 1 - (i - 1) * r % n + n) % n + 1])
				pre[j] = j;
			else
				pre[j] = pre[j - 1];
		}
		suf[n - 1] = n - 1;
		for (int j = n - 2; j >= 1; j--)
		{
			if (f[i - 1][j] - a[(j - (i - 1) * r % n + n) % n + 1] > f[i - 1][suf[j + 1]] - a[(suf[j + 1] - (i - 1) * r % n + n) % n + 1])
				suf[j] = j;
			else
				suf[j] = suf[j + 1];
		}
		for (int j = 1; j <= n - 1; j++)
		{
			int ans1 = f[i - 1][pre[j]] + a[(pre[j] - 1 - (i - 1) * r % n + n) % n + 1] - a[(j - (i - 1) * r % n + n) % n + 1];
			int ans2 = f[i - 1][suf[j]] + a[(j - 1 - (i - 1) * r % n + n) % n + 1] - a[(suf[j] - (i - 1) * r % n + n) % n + 1];
			if (ans1 > ans2) f[i][j] = ans1, g[i][j] = pre[j];
			else f[i][j] = ans2, g[i][j] = suf[j];
		}
	}
	ans[n] = 1;
	for (int i = 2; i <= n - 1; i++) if (f[n][i] > f[n][ans[n]]) ans[n] = i;
	printf("%d\n", f[n][ans[n]]);
	for (int i = n - 1; i >= 0; i--) ans[i] = g[i + 1][ans[i + 1]];
	for (int i = 0; i <= n; i++)
	{
		printf("%d", ans[i]);
		if (i != n) putchar(' ');
	}
	return 0;
}
