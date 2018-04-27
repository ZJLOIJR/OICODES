#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))

const int N = 2e5 + 3;

int n, k, m, tot = 0;
int st[N], to[N << 1], nx[N << 1], vis[N];
int f[N][2];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u)
{
	vis[u] = 1, f[u][0] = 0, f[u][1] = 1;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (!vis[v])
			dfs(v), f[u][0] += f[v][1], f[u][1] += min(f[v][0], f[v][1]);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &k);
		for (int j = 1; j <= k; j++)
			scanf("%d", &m), add(i, m), add(m, i);
	}
	dfs(1);
	printf("%d\n", min(f[1][0], f[1][1]));
	return 0;
}
