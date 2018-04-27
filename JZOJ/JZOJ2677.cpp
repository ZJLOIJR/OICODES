#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

typedef long long ll;
const int N = 3e4 + 3;

struct SegmentTree
{
	ll sum[N << 2];
	void change(int rt, int l, int r, int po, ll val)
	{
		if (l == r) { sum[rt] = val; return; }
		int mid = l + r >> 1;
		if (po <= mid) change(lson, l, mid, po, val);
		else change(rson, mid + 1, r, po, val);
		sum[rt] = sum[lson] + sum[rson];
	}
	ll qrysum(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return sum[rt];
		int mid = l + r >> 1; ll ret = 0;
		if (ql <= mid) ret += qrysum(lson, l, mid, ql, qr);
		if (mid + 1 <= qr) ret += qrysum(rson, mid + 1, r, ql, qr);
		return ret;
	}
} tree;

int n, q, u, v, tot = 0, cnt = 0, opt;
int st[N], to[N << 1], nx[N << 1];
int fa[N], tid[N], son[N], top[N], siz[N], dep[N];

inline void swap(int &a, int &b) { int t = a; a = b, b = t; }
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs1(int u)
{
	int mxsiz = 0, mxid = 0;
	siz[u] = 1;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != fa[u])
		{
			fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), siz[u] += siz[v];
			if (siz[v] > mxsiz) mxsiz = siz[v], mxid = v;
		}
	}
	son[u] = mxid;
}

void dfs2(int u, int p)
{
	top[u] = p, tid[u] = ++cnt;
	if (son[u]) dfs2(son[u], p);
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != fa[u] && v != son[u]) dfs2(v, v);
	}
}

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n - 1; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dfs1(1), dfs2(1, 1);
	for (int i = 1; i <= n; i++) scanf("%d", &u), tree.change(1, 1, n, tid[i], (ll)u);
	while (q--)
	{
		scanf("%d%d%d", &opt, &u, &v);
		if (opt == 1) tree.change(1, 1, n, tid[u], (ll)v);
		else
		{
			ll ans = 0;
			while (top[u] != top[v])
			{
				if (dep[top[u]] < dep[top[v]]) swap(u, v);
				ans += tree.qrysum(1, 1, n, tid[top[u]], tid[u]);
				u = fa[top[u]];
			}
			if (dep[u] < dep[v]) swap(u, v);
			ans += tree.qrysum(1, 1, n, tid[v], tid[u]);
			printf("%lld\n", ans);
		}
	}
	return 0;
}
