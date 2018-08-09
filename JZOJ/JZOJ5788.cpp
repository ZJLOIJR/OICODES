#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int max(int a, int b) { return a > b ? a : b; }
const int N = 5e2 + 7;

int n, m, a[N], f[N][N][2];
int tot, st[N], to[N << 1], nx[N << 1];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u, int from)
{
	f[u][1][0] = f[u][1][1] = a[u];
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v == from) continue;
		dfs(v, u);
		for (int j = m; j >= 0; j--)
			for (int k = m; k >= 0; k--)
			{
				if (j + k + 1 <= m) f[u][j + k + 1][0] = max(f[u][j + k + 1][0], f[u][j][1] + f[v][k][0]);
				if (j + k + 2 <= m)
				{
					f[u][j + k + 2][1] = max(f[u][j + k + 2][1], f[u][j][1] + f[v][k][1]);
					f[u][j + k + 2][0] = max(f[u][j + k + 2][0], f[u][j][0] + f[v][k][1]);
				}
			}
	}
}

int main()
{
	freopen("dostavljac.in", "r", stdin);
	freopen("dostavljac.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1, u, v; i <= n - 1; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dfs(1, 0);
	printf("%d\n", max(f[1][m][0], f[1][m][1]));

	fclose(stdin);
	fclose(stdout);
	return 0;
}
