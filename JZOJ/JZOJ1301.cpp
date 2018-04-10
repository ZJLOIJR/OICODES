#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e4 + 3;

int n, u, v, tot = 0, cnt = 0;
int st[N], to[N << 1], nx[N << 1], mx[N], siz[N];
int ans[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u, int from)
{
	siz[u] = 1;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != from)
		{
			dfs(v, u);
			siz[u] += siz[v];
			if (siz[v] > mx[u]) mx[u] = siz[v];
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n - 1; i++)
	{
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
	{
		if (n - siz[i] > mx[i]) mx[i] = n - siz[i];
		if (mx[i] <= n / 2) ans[++cnt] = i;
	}
	if (!cnt) printf("NONE\n");
	else for (int i = 1; i <= cnt; i++) printf("%d\n", ans[i]);
	return 0;
}
