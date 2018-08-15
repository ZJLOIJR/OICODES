#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int max(int a, int b) { return a > b ? a : b; }
const int N = 3e2 + 7, INF = 0x3f3f3f3f;

int n, m, ans, w[N], t[N];
int tot, st[N], to[N << 1], nx[N << 1], len[N << 1];
int f[N][N], g[N][N], h[N][N];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

void dfs(int u, int from)
{
	for (int i = t[u]; i <= m; i++) f[u][i] = g[u][i] = h[u][i] = w[u];
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
		{
			dfs(to[i], u);
			for (int j = m; j >= 0; j--)
				for (int k = m; k >= 0; k--)
				{
					if (j - k - len[i] >= 0) h[u][j] = max(h[u][j], g[u][k] + g[to[i]][j - k - len[i]]);
					if (j - k - 2 * len[i] >= 0) h[u][j] = max(h[u][j], f[to[i]][j - k - 2 * len[i]] + h[u][k]);
					if (j - k - 2 * len[i] >= 0) h[u][j] = max(h[u][j], f[u][k] + h[to[i]][j - k - 2 * len[i]]);
					if (j - k - 2 * len[i] >= 0) g[u][j] = max(g[u][j], g[u][k] + f[to[i]][j - k - 2 * len[i]]);
					if (j - k - len[i] >= 0) g[u][j] = max(g[u][j], f[u][k] + g[to[i]][j - k - len[i]]);
					if (j - k - 2 * len[i] >= 0) f[u][j] = max(f[u][j], f[u][k] + f[to[i]][j - k - 2 * len[i]]);
				}
		}
}

int main()
{
	freopen("toyuq.in", "r", stdin);
	freopen("toyuq.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 0; j <= m; j++) f[i][j] = g[i][j] = h[i][j] = -INF;
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	for (int i = 1; i <= n; i++) scanf("%d", t + i), t[i] = t[i] > 300 ? 300 : t[i];
	for (int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w);
	dfs(1, 0);
	for (int i = 1; i <= n; i++) for (int j = 0; j <= m; j++) ans = max(ans, max(max(f[i][j], g[i][j]), h[i][j]));
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
