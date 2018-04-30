#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 3e5 + 3;
const ll P = 998244353;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline void swap(int &a, int &b) { int t = a; a = b, b = t; }

int n, u, v, k, q, tot = 0;
int st[N], to[N << 1], nx[N << 1], fa[N];
ll ans, dep[N], power[N][51];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u])
			fa[to[i]] = u, dep[to[i]] = dep[u] + 1, dfs(to[i]);
}

int main()
{
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);

	n = read();
	for (int i = 1; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	dfs(1);
	for (int i = 1; i <= n; i++)
	{
		power[i][0] = 1LL;
		for (int j = 1; j <= 50; j++) power[i][j] = power[i][j - 1] * dep[i] % P;
	}
	q = read();
	while (q--)
	{
		u = read(), v = read(), k = read();
		ans = 0;
		if (dep[u] < dep[v]) swap(u, v);
		while (dep[u] > dep[v]) ans = (ans + power[u][k]) % P, u = fa[u];
		while (u != v) ans = (ans + power[u][k] + power[v][k]) % P, u = fa[u], v = fa[v];
		ans = (ans + power[u][k]) % P;
		printf("%lld\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
