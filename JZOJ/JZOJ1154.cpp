#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 1e3 + 3;

int n, m, u, v, tot = 0, ans = 0;
int w[N], f[N][2];
int st[N], to[N << 1], nx[N << 1], vis[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u)
{
	vis[u] = 1, f[u][0] = 0, f[u][1] = w[u];
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (!vis[v])
			dfs(v), f[u][0] += max(f[v][0], f[v][1]), f[u][1] += f[v][0];
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	for (int i = 1; i <= m; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	for (int i = 1; i <= n; i++)
		if (!vis[i])
		{
			dfs(i);
			ans += max(f[i][0], f[i][1]);
		}
	printf("%d\n", ans);
	return 0;
}
