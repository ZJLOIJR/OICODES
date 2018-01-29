#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 10007, M = 2007, INF = 0x3f3f3f3f;

int n, m, k, p, l, h, ans;
int x[N], y[N], low[N], high[N], g[N];
int f[N][M];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	memset(f, 0x3f, sizeof(f));
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++) *(x + i) = read(), *(y + i) = read(), low[i] = 1, high[i] = m;
	for (int i = 1; i <= k; i++)
		p = read(), l = read(), h = read(),
		low[p] = l + 1, high[p] = h - 1, g[p] = 1;
	for (int i = 1; i <= m; i++) f[0][i] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = x[i] + 1; j <= m + x[i]; j++) f[i][j] = min(f[i - 1][j - x[i]], f[i][j - x[i]]) + 1;
		for (int j = m + 1; j <= m + x[i]; j++) f[i][m] = min(f[i][m], f[i][j]);
		for (int j = 1; j <= m - y[i]; j++) f[i][j] = min(f[i][j], f[i - 1][j + y[i]]);
		for (int j = 1; j <= low[i] - 1; j++) f[i][j] = INF;
		for (int j = high[i] + 1; j <= m; j++) f[i][j] = INF;
	}
	ans = INF;
	for (int i = 1; i <= m; i++) ans = min(ans, f[n][i]);
	if (ans < INF) printf("1\n%d\n", ans);
	else
	{
		int i, j;
		for (i = n; i >= 1; i--)
		{
			for (j = 1; j <= m; j++) if (f[i][j] < INF) break;
			if (j <= m) break;
		}
		ans = 0;
		for (j = 1; j <= i; j++) ans += g[j];
		printf("0\n%d\n", ans);
	}
	return 0;
}
