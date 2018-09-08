#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;

int T;
int n, ret, a[N];
int tot = 0, st[N], to[N], nx[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u, int dep)
{
	if (dep & 1) ret ^= a[u];
	for (int i = st[u]; i; i = nx[i]) dfs(to[i], dep + 1);
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		tot = 0;
		memset(st, 0, sizeof(st));
		memset(to, 0, sizeof(to));
		memset(nx, 0, sizeof(nx));
		memset(a, 0, sizeof(a));
		scanf("%d", &n);
		for (int i = 2, f; i <= n; i++) scanf("%d", &f), add(f + 1, i);
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		ret = 0, dfs(1, 0);
		printf(ret ? "win\n" : "lose\n");
	}
	return 0;
}
