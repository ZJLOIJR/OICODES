#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 100007;
const ll INF = (1ll << 40);
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
ll min(ll a, ll b) { return a < b ? a : b; }

int n, m;
int dfn, son[N], size[N], top[N], fa[N], tid[N], arr[N], bot[N];
int tot, st[N], to[N << 1], nx[N << 1];
void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
ll p[N], f[N][2], g[N][2];

struct matrix
{
	ll v[2][2];
	matrix operator*(matrix a)
	{
		matrix c;
		c.v[0][0] = c.v[0][1] = c.v[1][0] = c.v[1][1] = INF;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
				{
					if (v[i][k] >= INF || a.v[k][j] >= INF) c.v[i][j] = min(c.v[i][j], INF);
					else c.v[i][j] = min(c.v[i][j], v[i][k] + a.v[k][j]);
				}
		return c;
	}
} mat[N];
#define lson rt << 1
#define rson rt << 1 | 1
matrix sum[N << 2];
void insert(int rt, int l, int r, int po)
{
	if (l == r) { sum[rt] = mat[arr[l]]; return; }
	int mid = l + r >> 1;
	if (po <= mid) insert(lson, l, mid, po);
	else insert(rson, mid + 1, r, po);
	sum[rt] = sum[lson] * sum[rson];
}
matrix query(int rt, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) return sum[rt];
	int mid = l + r >> 1; matrix ret;
	if (ql <= mid) ret = query(lson, l, mid, ql, qr);
	if (mid + 1 <= qr)
	{
		if (ql <= mid) ret = ret * query(rson, mid + 1, r, ql, qr);
		else ret = query(rson, mid + 1, r, ql, qr);
	}
	return ret;
}

void dfs1(int u)
{
	size[u] = 1;
	int mxsiz = 0;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u])
		{
			fa[to[i]] = u, dfs1(to[i]), size[u] += size[to[i]];
			if (size[to[i]] > mxsiz) mxsiz = size[to[i]], son[u] = to[i];
		}
}
void dfs2(int u, int tp)
{
	tid[u] = ++dfn, arr[dfn] = u, top[u] = tp;
	if (son[u]) dfs2(son[u], tp), bot[u] = bot[son[u]];
	else bot[u] = u;
	for (int i = st[u]; i; i = nx[i]) if (to[i] != fa[u] && to[i] != son[u]) dfs2(to[i], to[i]);
}
void dp(int u)
{
	f[u][0] = 0, f[u][1] = p[u];
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u])
		{
			dp(to[i]);
			f[u][0] += f[to[i]][1], f[u][1] += min(f[to[i]][0], f[to[i]][1]);
		}
	g[u][0] = f[u][0] - f[son[u]][1], g[u][1] = f[u][1] - min(f[son[u]][0], f[son[u]][1]);
	mat[u].v[0][0] = INF, mat[u].v[0][1] = g[u][0], mat[u].v[1][0] = mat[u].v[1][1] = g[u][1];
}


void init()
{
	n = read(), m = read(), scanf("%*s");
	for (int i = 1; i <= n; i++) p[i] = read();
	for (int i = 1, u, v; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	dfs1(1), dfs2(1, 1), dp(1);
	for (int i = 1; i <= n; i++) insert(1, 1, n, i);
}

void doit(int u, int v)
{
	if (v == -1) mat[u].v[0][1] = g[u][0], mat[u].v[1][0] = mat[u].v[1][1] = g[u][1];
	else if (v) mat[u].v[0][1] = INF;
	else mat[u].v[1][0] = mat[u].v[1][1] = INF;
	while (u)
	{
		matrix res = query(1, 1, n, tid[top[u]], tid[bot[u]]);
		insert(1, 1, n, tid[u]);
		matrix now = query(1, 1, n, tid[top[u]], tid[bot[u]]);
		u = fa[top[u]];
		mat[u].v[0][1] += now.v[1][1] - res.v[1][1];
		mat[u].v[1][0] += min(now.v[0][1], now.v[1][1]) - min(res.v[0][1], res.v[1][1]);
		mat[u].v[1][1] += min(now.v[0][1], now.v[1][1]) - min(res.v[0][1], res.v[1][1]);
	}
}

void solve()
{
	while (m--)
	{
		int a = read(), x = read(), b = read(), y = read();
		doit(a, x), doit(b, y);
		matrix res = query(1, 1, n, tid[1], tid[bot[1]]);
		ll ans = min(res.v[0][1], res.v[1][1]);
		if (ans >= INF) printf("-1\n");
		else printf("%lld\n", ans);
		doit(a, -1), doit(b, -1);
	}
}

int main()
{
	freopen("testdata1.in", "r", stdin);
	freopen("output", "w", stdout);
	//freopen("defense.in", "r", stdin);
	//freopen("defense.out", "w", stdout);
	init();
	solve();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
