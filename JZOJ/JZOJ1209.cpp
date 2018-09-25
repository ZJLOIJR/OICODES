#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e4 + 7;

int n, m, ret;
int tot, st[N], to[N << 1], nx[N << 1], dep[N], anc[N][16];
ll ans, sum[N], len[N << 1];

void add(int u, int v, ll w) { to[++tot] = v, nx[tot] = st[u], st[u] = tot, len[tot] = w; }

void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
		{
			int v = to[i];
			anc[v][0] = u, sum[v] = sum[u] + len[i], dep[v] = dep[u] + 1;
			dfs(v);
		}
}

void swap(int &a, int &b) { int t = a; a = b, b = t; }
int getlca(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 15; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	for (int i = 15; i >= 0; i--) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++)
	{
		int u, v; ll w;
		scanf("%d%d%lld", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	dep[1] = 1, dfs(1);
	for (int j = 1; j <= 15; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	while (m--)
	{
		int u, v, lca;
		scanf("%d%d", &u, &v);
		lca = getlca(u, v);
		if (lca == u && dep[u] <= dep[v]) ret++, ans += sum[v] - sum[u];
	}
	printf("%d\n%lld\n", ret, ans);
	return 0;
}
