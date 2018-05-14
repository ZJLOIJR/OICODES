#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 5e4 + 3, M = 1e5 + 3;
inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline ll min(ll a, ll b) { return a < b ? a : b; }

ll P;
int n, m, q, u, v;
int tot = 0, st[N], to[N << 1], nx[N << 1], len[N << 1], dep[N], anc[N][21], mi[N][21];
int fa[N];
struct edg { int from, to, len; } a[M];
inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
void init()
{
	memset(mi, 0x3f, sizeof(mi));
	n = read(), m = read(), q = read(), P = read();
	for (int i = 1; i <= m; i++) a[i].from = read(), a[i].to = read(), a[i].len = read();
}
void maketree()
{
	sort(a + 1, a + m + 1, [](edg x, edg y){ return x.len > y.len; });
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1, cnt = 0; i <= m; i++)
	{
		int u = getfa(a[i].from), v = getfa(a[i].to);
		if (u != v) cnt++, add(a[i].from, a[i].to, a[i].len), add(a[i].to, a[i].from, a[i].len), fa[v] = u;
		if (cnt == n - 1) return;
	}
}
void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			anc[to[i]][0] = u, dep[to[i]] = dep[u] + 1, mi[to[i]][0] = len[i], dfs(to[i]);
}
void rmq()
{
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1], mi[i][j] = min(mi[i][j - 1], mi[anc[i][j - 1]][j - 1]);
}
void solve()
{
	ll ans = 1LL;
	while (q--)
	{
		ll mival = 2147483647LL;
		u = read(), v = read();
		if (dep[u] < dep[v]) { int t = u; u = v, v = t; }
		for (int i = 20; i >= 0; i--)
			if (dep[anc[u][i]] >= dep[v])
				mival = min(mival, mi[u][i]), u = anc[u][i];
		if (u == v) { ans = ans * mival % P; continue; }
		for (int i = 20; i >= 0; i--)
			if (anc[u][i] != anc[v][i])
				mival = min(mival, min(mi[u][i], mi[v][i])), u = anc[u][i], v = anc[v][i];
		mival = min(mival, min(mi[u][0], mi[v][0]));
		ans = ans * mival % P;
	}
	printf("%lld\n", ans);
}
int main()
{
	init();
	maketree();
	dep[1] = 0, dfs(1);
	rmq();
	solve();
	return 0;
}
