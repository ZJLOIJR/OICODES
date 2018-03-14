#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e6 + 3;

int n, m, u, v, opt, tot = 0;
int st[N], fa[N], to[N << 1], nx[N << 1], dep[N];
int col[N << 1], id[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], id[tot] = w, st[u] = tot; }
inline void swap(int &a, int &b) { int t = a; a = b, b = t; }

void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != fa[u]) fa[v] = u, id[v] = i, dep[v] = dep[u] + 1, dfs(v);
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n - 1; i++)
		u = read(), v = read(), add(u, v, i), add(v, u, i);
	dfs(1);
	while (m--)
	{
		opt = read();
		if (opt == 1)
		{
			u = read();
			while (u)
			{
				if (col[id[u]]) { printf("%d\n", id[u]); }
				u = fa[u];
			}
			if (!col[id[u]]) printf("0\n");
		}
		else
		{
			u = read(), v = read();
			if (dep[u] < dep[v]) swap(u, v);
			while (dep[u] > dep[v])
			{
				if (fa[u] == v) { u = fa[u]; break; }
				col[id[u]] = 1, u = fa[u];
			}
			while (u != v)
			{
				if (fa[u] == fa[v]) break;
				col[id[u]] = col[id[v]] = 1;
				u = fa[u], v = fa[v];
			}
		}
	}
	return 0;
}
