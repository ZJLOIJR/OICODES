#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int max(int a, int b) { return a > b ? a : b; }

int T;
int n, k, a, tot, st[N], to[N << 1], nx[N << 1];
int maxval, f[N][2];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u, int from)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
			dfs(to[i], u), f[u][0] += max(f[to[i]][0], f[to[i]][1]);
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
			f[u][1] = max(f[u][1], f[u][0] - max(f[to[i]][0], f[to[i]][1]) + f[to[i]][0] + 1);
}

int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);

	scanf("%d", &T);
	while (T--)
	{
		tot = 0;
		memset(st, 0, sizeof(st));
		memset(to, 0, sizeof(to));
		memset(nx, 0, sizeof(nx));
		memset(f, 0, sizeof(f));
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n - 1; i++) scanf("%d", &a), add(i + 1, a), add(a, i + 1);
		dfs(1, 0);
		maxval = max(f[1][0], f[1][1]);
		if (maxval * 2 >= k) printf("%d\n", k / 2 + (k % 2));
		else printf("%d\n", maxval + k - maxval * 2);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
