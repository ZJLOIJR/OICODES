#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e4 + 7;

int T;
int tot = 0, st[N], to[N << 1], nx[N << 1], len[N << 1];
int n, m, anc[N][21], sum[N], dep[N];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			dep[to[i]] = dep[u] + 1, anc[to[i]][0] = u, sum[to[i]] = sum[u] + len[i], dfs(to[i]);
}
int getlca(int u, int v)
{
	if (dep[u] < dep[v]) u ^= v ^= u ^= v;
	for (int i = 20; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	for (int i = 20; i >= 0; i--) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		memset(st, 0, sizeof(st));
		memset(nx, 0, sizeof(nx));
		memset(anc, 0, sizeof(anc));
		tot = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w);
		dep[1] = 0, dfs(1);
		for (int j = 1; j <= 20; j++)
			for (int i = 1; i <= n; i++)
				anc[i][j] = anc[anc[i][j - 1]][j - 1];
		while (m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			int lca = getlca(u, v);
			printf("%d\n", sum[u] + sum[v] - 2 * sum[lca]);
		}
		putchar('\n');
	}
	return 0;
}
