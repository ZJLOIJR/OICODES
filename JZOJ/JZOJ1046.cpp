#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int max(int a, int b) { return a > b ? a : b; }
const int N = 1e2 + 7;

int n, m, a[N];
int tot = 0, st[N], to[N << 1], nx[N << 1];
int f[N][N][2];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u, int from)
{
	for (int j = 1; j <= m; j++) f[u][j][1] = a[u];
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
		{
			int v = to[i];
			dfs(v, u);
			for (int j = 1; j <= m; j++) f[u][j][0] = max(f[u][j][0], max(f[v][j][0], f[v][j][1]));
			for (int j = m; j > 0; j--)
				for (int k = 0; k < j; k++)
					f[u][j][1] = max(f[u][j][1], max(f[v][k][0], f[v][k][1]) + f[u][j - k][1]);
		}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dfs(1, 0);
	printf("%d\n", max(f[1][m][0], f[1][m][1]));
	return 0;
}
