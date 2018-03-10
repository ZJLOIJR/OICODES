#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 4e4 + 3;

int root, n, m, u, v, tot = 0;
int st[N], to[N << 1], nx[N << 1], f[N][21], dep[N], buc[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
inline void swap(int &a, int &b) { int t = a; a = b, b = t; }

void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != f[u][0])
			f[v][0] = u, dep[v] = dep[u] + 1, dfs(v);
	}
}

int LCA(int u, int v)
{
	if (dep[v] > dep[u]) swap(u, v);
	for (int i = 20; i >= 0; i--)
		if (dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if (u == v) return u;
	for (int i = 20; i >= 0; i--)
		if (f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}

void init()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		u = read(), v = read();
		if (v == -1) root = u;
		else
		{
			add(u, v), add(v, u);
			buc[u] = buc[v] = 1;
		}
	}
	f[root][0] = 0, dep[root] = 1, dfs(root);
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= 40000; i++)
			if (buc[i]) f[i][j] = f[f[i][j - 1]][j - 1];
}

void solve()
{
	m = read();
	while (m--)
	{
		u = read(), v = read();
		if (u == v || !buc[u] || !buc[v]) printf("0\n");
		else
		{
			int lca = LCA(u, v);
			if (lca == u) printf("1\n");
			else if (lca == v) printf("2\n");
			else printf("0\n");
		}
	}
}

int main()
{
	init();
	solve();
	return 0;
}
