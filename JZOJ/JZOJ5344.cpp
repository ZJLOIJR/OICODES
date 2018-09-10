#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int max(int a, int b) { return a > b ? a : b; }
const int N = 2e3 + 7;

int n, m, cnt;
int f[N][N], v[N], p[N];

int tot, st[N], to[N << 1], nx[N << 1], out[N], dfn[N], arr[N];
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u, int from)
{
	arr[dfn[u] = ++cnt] = u;
	for (int i = st[u]; i; i = nx[i]) if (to[i] != from) dfs(to[i], u);
	out[u] = cnt;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", v + i, p + i);
	for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), add(x, y), add(y, x);
	dfs(1, 0);
	for (int i = n; i; i--)
	{
		int x = arr[i];
		for (int j = 0; j <= m; j++)
		{
			if (j + p[x] <= m) f[i][j] = max(f[i][j], f[i + 1][j + p[x]] + v[x]);
			f[i][j] = max(f[i][j], f[out[x] + 1][j]);
		}
	}
	int ans = 0;
	for (int i = 0; i <= m; i++) ans = max(ans, f[1][i]);
	printf("%d\n", ans);
	return 0;
}
