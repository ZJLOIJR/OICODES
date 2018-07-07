#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int min(int a, int b) { return a < b ? a : b; }

const int N = 1e5 + 7;

int n, m, tot = 0, c[N], st[N], to[N << 1], nx[N << 1];
int f[N][2];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u, int from)
{
	if (u > m) f[u][0] = f[u][1] = 1;
	else f[u][c[u]] = 1, f[u][!c[u]] = 0x3f3f3f3f;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
		{
			dfs(to[i], u);
			f[u][0] += min(f[to[i]][0] - 1, f[to[i]][1]);
			f[u][1] += min(f[to[i]][1] - 1, f[to[i]][0]);
		}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++) c[i] = read();
	for (int i = 1, u, v; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	dfs(n, 0);
	printf("%d\n", min(f[n][0], f[n][1]));
	return 0;
}
