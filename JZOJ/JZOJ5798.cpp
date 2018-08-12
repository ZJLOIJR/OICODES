#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 3e5 + 7, P = 1e9 + 7;

int ans = 1;
int n, m, a[N], b[N], lca[N];
int tot, st[N], to[N << 1], nx[N << 1], dep[N], anc[N][21];
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			dep[to[i]] = dep[u] + 1, anc[to[i]][0] = u, dfs(to[i]);
}

int findlca(int u, int v)
{
	if (dep[u] < dep[v]) u ^= v ^= u ^= v;
	for (int i = 20; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	for (int i = 20; i >= 0; i--) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

int fa[N], dir[N];
int getfa(int x)
{
	if (fa[x] == x) return x;
	int father = getfa(fa[x]);
	dir[x] ^= dir[fa[x]];
	return fa[x] = father;
}

int main()
{
	freopen("usmjeri.in", "r", stdin);
	freopen("usmjeri.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	anc[1][0] = 1, dfs(1);
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1, u, v; i <= m; i++)
	{
		scanf("%d%d", a + i, b + i);
		lca[i] = findlca(a[i], b[i]);
		u = getfa(a[i]), v = getfa(b[i]);
		while (dep[u] - dep[lca[i]] >= 2)
			fa[getfa(u)] = getfa(anc[u][0]), u = getfa(u);
		while (dep[v] - dep[lca[i]] >= 2)
			fa[getfa(v)] = getfa(anc[v][0]), v = getfa(v);
	}
	for (int i = 1; i <= m; i++)
	{
		if (a[i] == lca[i] || b[i] == lca[i]) continue;
		int u = getfa(a[i]), v = getfa(b[i]);
		if (u == v)
		{
			if ((dir[a[i]] ^ dir[b[i]]) == 0) { printf("0\n"); return 0; }
			continue;
		}
		fa[u] = v, dir[u] = dir[a[i]] ^ dir[b[i]] ^ 1;
	}
	for (int i = 2; i <= n; i++) if (getfa(i) == i) ans = ans * 2LL % P;
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
