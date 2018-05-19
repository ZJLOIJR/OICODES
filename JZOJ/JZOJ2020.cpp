#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e3 + 7;

int n, q, u, v, w, tot = 0, dep[N], anc[N][11], sum[N][11];
int st[N], to[N << 1], nx[N << 1], len[N << 1];
inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			anc[to[i]][0] = u, sum[to[i]][0] = len[i], dep[to[i]] = dep[u] + 1, dfs(to[i]);
}

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i < n; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w);
	dfs(1);
	for (int j = 1; j <= 10; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1], sum[i][j] = sum[i][j - 1] + sum[anc[i][j - 1]][j - 1];
	while (q--)
	{
		scanf("%d%d", &u, &v);
		int ans = 0;
		if (dep[u] < dep[v]) { int t = u; u = v, v = t; }
		for (int i = 10; i >= 0; i--)
			if (dep[anc[u][i]] >= dep[v])
				ans += sum[u][i], u = anc[u][i];
		if (u == v) { printf("%d\n", ans); continue; }
		for (int i = 10; i >= 0; i--)
			if (anc[u][i] != anc[v][i])
				ans += sum[u][i] + sum[v][i], u = anc[u][i], v = anc[v][i];
		ans += sum[u][0] + sum[v][0];
		printf("%d\n", ans);
	}
	return 0;
}
