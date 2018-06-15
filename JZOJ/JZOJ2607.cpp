#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

inline int max(int a, int b) { return a > b ? a : b; }

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

const int N = 1e4 + 7, M = 1e5 + 7;

int n, m, q;
struct edg { int from, to, len; } edge[M];
int fa[N];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int cmp(edg x, edg y) { return x.len < y.len; }

int tot = 0, st[N], to[N << 1], nx[N << 1], len[N << 1], dep[N];
inline void add(int u, int v, int w)
{
	to[++tot] = v, nx[tot] = st[u], st[u] = tot, len[tot] = w;
	to[++tot] = u, nx[tot] = st[v], st[v] = tot, len[tot] = w;
}
int mx[N][21], anc[N][21];

void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i]) if (to[i] != anc[u][0]) anc[to[i]][0] = u, mx[to[i]][0] = len[i], dep[to[i]] = dep[u] + 1, dfs(to[i]);
}

int solve(int u, int v)
{
	if (dep[u] < dep[v]) u ^= v ^= u ^= v;
	int ans = 0;
	for (int i = 20; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) ans = max(ans, mx[u][i]), u = anc[u][i];
	if (u == v) return ans;
	for (int i = 20; i >= 0; i--) if (anc[u][i] != anc[v][i]) ans = max(ans, max(mx[u][i], mx[v][i])), u = anc[u][i], v = anc[v][i];
	return max(ans, max(mx[u][0], mx[v][0]));
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++) edge[i].from = read(), edge[i].to = read(), edge[i].len = read();
	sort(edge + 1, edge + m + 1, cmp);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1, cnt = 0, u, v; i <= m; i++)
	{
		u = getfa(edge[i].from), v = getfa(edge[i].to);
		if (u != v) add(edge[i].from, edge[i].to, edge[i].len), cnt++, fa[v] = u;
		if (cnt == n - 1) break;
	}
	dfs(1);
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1], mx[i][j] = max(mx[i][j - 1], mx[anc[i][j - 1]][j - 1]);
	q = read();
	for (int i = 1, u, v; i <= q; i++) u = read(), v = read(), printf("%d\n", solve(u, v));
	return 0;
}
