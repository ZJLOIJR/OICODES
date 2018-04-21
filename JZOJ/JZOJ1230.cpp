//60 points做法
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 5e4 + 3, INF = 0x3f3f3f3f;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, u, v, q, tot = 0;
int st[N], to[N << 1], nx[N << 1], c[N], arr[N];
int dep[N], fa[N];

void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != fa[u]) fa[v] = u, dep[v] = dep[u] + 1, dfs(v);
	}
}

void swap(int &a, int &b) { int t = a; a = b, b = t; }
int LCA(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	while (dep[u] > dep[v]) u = fa[u];
	while (u != v) u = fa[u], v = fa[v];
	return u;
}

int main()
{
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	
	n = read();
	for (int i = 1; i <= n; i++) c[i] = read();
	for (int i = 1; i <= n - 1; i++) u = read(), v = read(), add(u, v), add(v, u);
	dep[1] = 1, fa[1] = 0, dfs(1);
	q = read();
	while (q--)
	{
		u = read(), v = read();
		int lca = LCA(u, v), ans = 0, mi, miu, mxv;
		mi = INF;
		while (dep[u] >= dep[lca])
		{
			ans = max(ans, c[u] - mi);
			mi = min(mi, c[u]), u = fa[u];
		}
		miu = mi, mi = INF, mxv = -INF;
		arr[0] = 0;
		while (dep[v] >= dep[lca]) arr[++arr[0]] = v, v = fa[v];
		for (int i = arr[0]; i >= 1; i--)
		{
			mxv = max(mxv, c[arr[i]]);
			ans = max(ans, c[arr[i]] - mi);
			mi = min(mi, c[arr[i]]);
		}
		ans = max(ans, mxv - miu);
		printf("%d\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
