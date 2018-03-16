#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 15007, M = 30007;

int n, m, u, v, w, q, tot = 0, cnt = 0, ans;

int st[N], to[N << 1], nx[N << 1], len[N << 1];
int f[N][21], mx[N][21], dep[N], fa[N];
struct edg { int from, to, l; } E[M];

inline int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
inline int max(int a, int b) { return a > b ? a : b; }
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

void dfs(int x, int fr)
{
	for (int i = st[x]; i; i = nx[i])
	{
		int v = to[i];
		if (fr != v)
			f[v][0] = x, mx[v][0] = len[i], dep[v] = dep[x] + 1, dfs(v, x);;
	}
}

void init()
{
	n = read(), m = read(), q = read();
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
		E[i].from = read(), E[i].to = read(), E[i].l = read();
	sort(E + 1, E + m + 1, [](edg a, edg b){ return a.l < b.l; });
	for (int i = 1; i <= m; i++)
	{
		u = getfa(E[i].from), v = getfa(E[i].to);
		if (u != v)
			fa[v] = u, cnt++, add(E[i].from, E[i].to, E[i].l), add(E[i].to, E[i].from, E[i].l);
		if (cnt == n - 1) break;
	}
	dep[1] = 1;
	dfs(1, 0);
	for (int j = 1; (1 << j) <= n; j++)
		for (int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j - 1]][j - 1],
			mx[i][j] = max(mx[i][j - 1], mx[f[i][j - 1]][j - 1]);
}

void solve()
{
	while (q--)
	{
		u = read(), v = read();
		ans = 0;
		if (dep[u] < dep[v]) swap(u, v);
		for (int i = 20; i >= 0; i--)
			if (dep[f[u][i]] >= dep[v])
				ans = max(ans, mx[u][i]), u = f[u][i];
		if (u == v) { printf("%d\n", ans); continue; }
		for (int i = 20; i >= 0; i--)
			if (f[u][i] != f[v][i])
				ans = max(ans, max(mx[u][i], mx[v][i])), u = f[u][i], v = f[v][i];
		ans = max(ans, max(mx[u][0], mx[v][0]));
		printf("%d\n", ans);
	}
}

int main()
{
	init();
	solve();
	return 0;
}
