#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 5e3 + 3, P = 1e4 + 3;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, p, f, tot = 0, cnt = 0, ans;
int st[N], to[N << 1], nx[N << 1], siz[N], dfn[N], w[N], v[N];
int dp[N][P];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u, int from)
{
	siz[u] = 1, dfn[++cnt] = u;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from) dfs(to[i], u), siz[u] += siz[to[i]];
}

int main()
{
	freopen("medicine.in", "r", stdin);
	freopen("medicine.out", "w", stdout);

	n = read(), p = read();
	for (int i = 1; i <= n; i++)
	{
		w[i] = read(), f = read(), v[i] = read();
		if (i != f) add(f, i), add(i, f);
	}
	dfs(1, 0);
	memset(dp, -0x3f, sizeof(dp));
	dp[1][0] = ans = 0;
	for (int i = 1; i <= cnt; i++)
	{
		int x = dfn[i];
		for (int j = 0; j <= p; j++)
		{
			if (dp[i][j] < 0) continue;
			if (j + w[x] <= p) dp[i + 1][j + w[x]] = max(dp[i + 1][j + w[x]], dp[i][j] + v[x]);
			dp[i + siz[x]][j] = max(dp[i + siz[x]][j], dp[i][j]);
			ans = max(ans, dp[i][j]);
		}
	}
	for (int i = 0; i <= p; i++) ans = max(ans, dp[cnt + 1][i]);
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
