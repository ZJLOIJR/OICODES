
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

int n, m, d;
ll p[N], g[N][2];

int tot, st[N], to[N << 1], nx[N << 1];
void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

int dfn, dep[N], son[N], size[N], top[N], fa[N], tid[N], arr[N];
void dfs1(int u)
{
	size[u] = 1;
	int mxsiz = 0;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u])
		{
			dep[to[i]] = dep[u] + 1, fa[to[i]] = u;
			dfs1(to[i]);
			size[u] += size[to[i]];
			if (size[to[i]] > mxsiz) mxsiz = size[to[i]], son[u] = to[i];
		}
}
void dfs2(int u, int tp)
{
	tid[u] = ++dfn, arr[dfn] = u, top[u] = tp;
	if (son[u]) dfs2(son[u], tp);
	for (int i = st[u]; i; i = nx[i]) if (to[i] != fa[u] && to[i] != son[u]) dfs2(to[i], to[i]);
}
void dp(int u)
{
	g[u][0] = 0, g[u][1] = p[u];
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u])
		{
			dp(to[i]);
			if (to[i] != son[u]) g[u][0] += g[to[i]][1], g[u][1] += min(g[to[i]][0], g[to[i]][1]);
		}
}

struct matrix
{
	ll v[2][2];
	matrix operator*(matrix a)
	{
		matrix c;
		memset(c.v, 0x3f, sizeof(c.v));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					c.v[i][j] = min(c.v[i][j], v[i][k] + a.v[k][j]);
		return c;
	}
};
#define lson rt << 1
#define rson rt << 1 | 1
matrix sum[N << 2];
void insert(int rt, int l, int r, int po, int val)
{
	if (l == r)
	{
		if (val == 2)
		{
			sum[rt].v[0][0] = INF;
			sum[rt].v[0][1] = g[arr[l]][0];
			sum[rt].v[1][0] = sum[rt].v[1][1] = g[arr[l]][1];
		}
		else if (val == 1) sum[rt].v[1][0] = sum[rt].v[1][1] = INF;
		else sum[rt].v[0][1] = INF;
		return;
	}
	int mid = l + r >> 1;
	if (po <= mid) insert(lson, l, mid, po, val);
	else insert(rson, mid + 1, r, po, val);
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

void init()
{
	n = read(), m = read(), scanf("%*s");
	for (int i = 1; i <= n; i++) p[i] = read();
	for (int i = 1, u, v; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	memset(g, 0x3f, sizeof(g));
	dep[1] = 1, dfs1(1), dfs2(1, 1), dp(1);
	for (int i = 1; i <= n; i++) insert(1, 1, n, i, 2);
	for (int i = 1; i <= n; i++) if (top[i] == 1 && dep[i] > dep[d]) d = i;
}

void solve()
{
	while (m--)
	{
		int a = read(), x = read(), b = read(), y = read(), ta = fa[top[a]], tb = fa[top[b]];
		while (ta) insert(1, 1, n, tid[ta], x), ta = fa[top[ta]];
		while (tb) insert(1, 1, n, tid[tb], y), tb = fa[top[tb]];
		insert(1, 1, n, tid[a], x);
		insert(1, 1, n, tid[b], y);
		matrix res = query(1, 1, n, tid[1], tid[d] - 1);
		//printf("%lld %lld\n%lld %lld\n", res.v[0][0], res.v[0][1], res.v[1][0], res.v[1][1]);
		ll g0 = g[d][0], g1 = g[d][1];
		if (d == a)
		{
			if (x) g0 = INF; else g1 = INF;
		}
		else if (d == b)
		{
			if (y) g0 = INF; else g1 = INF;
		}
		ll f0 = min(res.v[0][0] + g0, res.v[0][1] + g1), f1 = min(res.v[1][0] + g0, res.v[1][1] + g1);
		//printf("%lld\n", min(f0, f1));
		ta = fa[top[a]], tb = fa[top[b]];
		while (ta) insert(1, 1, n, tid[ta], 2), ta = fa[top[ta]];
		while (tb) insert(1, 1, n, tid[tb], 2), tb = fa[top[tb]];
		insert(1, 1, n, tid[a], 2);
		insert(1, 1, n, tid[b], 2);
	}
}

int main()
{
	freopen("input", "r", stdin);
	//freopen("defense.in", "r", stdin);
	//freopen("defense.out", "w", stdout);
	init();
	//matrix res = query(1, 1, n, tid[1], tid[1]);
	//res = res * query(1, 1, n, tid[5], tid[5]);
	//res = res * query(1, 1, n, tid[3], tid[3]);
	//printf("%lld %lld\n%lld %lld\n", res.v[0][0], res.v[0][1], res.v[1][0], res.v[1][1]);
	//ll f0 = min(res.v[0][0] + g[4][0], res.v[0][1] + g[4][1]), f1 = min(res.v[1][0] + g[4][0], res.v[1][1] + g[4][1]);
	//printf("%lld %lld\n", f0, f1);
	solve();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
