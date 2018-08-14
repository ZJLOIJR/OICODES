#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e5 + 7;
const ll P = 1e9 + 7;

int n, q;
int tot, st[N], to[N << 1], nx[N << 1];
int dep[N], anc[N][21];
ll f[N], g[N], d[N], sumf[N], sumg[N];

inline void add(int u, int v) { d[u]++, d[v]++, to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

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

void dfsf(int u)
{
	f[u] = d[u];
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			dfsf(to[i]), f[u] += f[to[i]];
}
void dfsg(int u)
{
	int sum = 0;
	for (int i = st[u]; i; i = nx[i]) if (to[i] != anc[u][0]) sum += f[to[i]];
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			g[to[i]] = d[u] + g[u] + sum - f[to[i]], dfsg(to[i]);
}
void dfss(int u)
{
	sumf[u] = sumf[anc[u][0]] + f[u];
	sumg[u] = sumg[anc[u][0]] + g[u];
	for (int i = st[u]; i; i = nx[i]) if (to[i] != anc[u][0]) dfss(to[i]);
}

int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);

	scanf("%d%d", &n, &q);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dep[1] = 1, dfs(1);
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	for (int i = 1; i <= n; i++) d[i] /= 2;
	dfsf(1), dfsg(1), dfss(1);
	while (q--)
	{
		int u, v, lca;
		scanf("%d%d", &u, &v);
		lca = findlca(u, v);
		printf("%lld\n", (sumf[u] - sumf[lca] + sumg[v] - sumg[lca]) % P);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
