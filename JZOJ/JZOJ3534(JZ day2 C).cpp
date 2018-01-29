#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 10007, M = 50007, INF = 0x7f7f7f7f;

int n, m, u, v, w, q, tot = 0, cnt = 0, ans;

int st[N], to[N << 1], nx[N << 1], len[N << 1];
int f[N][21], mi[N][21], dep[N];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
inline int min(int a, int b) { return a < b ? a : b; }

void dfs(int x, int fr)
{
	for (int i = st[x]; i; i = nx[i])
	{
		int v = to[i];
		if (fr != v)
		{
			f[v][0] = x, mi[v][0] = len[i], dep[v] = dep[x] + 1;
			dfs(v, x);
		}
	}
}

struct edg { int from, to, l; } E[M];

int fa[N];
inline int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int cmp(edg x, edg y) { return x.l > y.l; }
void init()
{
	memset(mi, 0x3f, sizeof(mi));
	n = read(), m = read();
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
		E[i].from = read(), E[i].to = read(), E[i].l = read();
	sort(E + 1, E + m + 1, cmp);
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
			mi[i][j] = min(mi[i][j - 1], mi[f[i][j - 1]][j - 1]);
}

void solve()
{
	q = read();
	while (q--)
	{
		u = read(), v = read();
		if (getfa(u) != getfa(v))
		{
			printf("-1\n");
			continue;
		}
		ans = INF;
		if (dep[u] < dep[v]) swap(u, v);
		for (int i = 20; i >= 0; i--)
			if (dep[f[u][i]] >= dep[v])
				ans = min(ans, mi[u][i]), u = f[u][i];
		if (u == v) { printf("%d\n", ans); continue; }
		for (int i = 20; i >= 0; i--)
			if (f[u][i] != f[v][i])
				ans = min(ans, min(mi[u][i], mi[v][i])), u = f[u][i], v = f[v][i];
		ans = min(ans, min(mi[u][0], mi[v][0]));
		printf("%d\n", ans);
	}
}

int main()
{
	init();
	solve();
	return 0;
}
