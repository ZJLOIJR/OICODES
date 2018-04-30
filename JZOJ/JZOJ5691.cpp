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

int n, q, u, v, k, tot = 0;
int st[N], to[N << 1], nx[N << 1], dep[N], f[N][21];
ll sum[N][51];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u)
{
	ll d = dep[u];
	for (int i = 1; i <= 50; i++) sum[u][i] = (sum[f[u][0]][i] + d) % P, d = d * dep[u] % P;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != f[u][0])
			f[to[i]][0] = u, dep[to[i]] = dep[u] + 1, dfs(to[i]);
}
int LCA(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 20; i >= 0; i--) if (dep[f[u][i]] >= dep[v]) u = f[u][i];
	if (u == v) return u;
	for (int i = 20; i >= 0; i--) if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
	return f[u][0];
}

int main()
{
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	
	n = read();
	for (int i = 1; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	dfs(1);
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j - 1]][j - 1];
	q = read();
	while (q--)
	{
		u = read(), v = read(), k = read();
		int lca = LCA(u, v);
		printf("%lld\n", ((sum[u][k] + sum[v][k] - sum[lca][k] - sum[f[lca][0]][k] + P + P) % P));
	}
	

	fclose(stdin);
	fclose(stdout);
	return 0;
}
