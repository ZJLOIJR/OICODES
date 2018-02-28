#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 1e5 + 3;

int n, m, R, P, u, v, tot = 0, dfn = 0;
int st[N], to[N << 1], nx[N << 1];
int w[N], siz[N], top[N], son[N], dep[N], fa[N], tid[N];

void swap(int &a, int &b) { int t = a; a = b, b = t; }
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

struct SegmentTree
{
	int sum[N << 2], inc[N << 2];

	void down(int rt, int l, int r)
	{
		if (inc[rt] == 0) return;
		if (l != r)
			inc[lson] = (inc[lson] + inc[rt]) % P,
			inc[rson] = (inc[rson] + inc[rt]) % P;
		sum[rt] = (sum[rt] + inc[rt] * (r - l + 1)) % P;
		inc[rt] = 0;
	}
	
	void insert(int rt, int l, int r, int po, int val)
	{
		if (l == r) { sum[rt] = val; return; }
		int mid = l + r >> 1;
		if (po <= mid) insert(lson, l, mid, po, val);
		else insert(rson, mid + 1, r, po, val);
		sum[rt] = (sum[lson] + sum[rson]) % P, inc[rt] = 0;
	}

	void plus(int rt, int l, int r, int ql, int qr, int val)
	{
		down(rt, l, r);
		if (ql <= l && r <= qr) { inc[rt] = (inc[rt] + val) % P; return; }
		int mid = l + r >> 1;
		if (ql <= mid) plus(lson, l, mid, ql, qr, val);
		if (mid + 1 <= qr) plus(rson, mid + 1, r, ql, qr, val);
		down(lson, l, mid), down(rson, mid + 1, r);
		sum[rt] = (sum[lson] + sum[rson]) % P;
	}

	int query(int rt, int l, int r, int ql, int qr)
	{
		down(rt, l, r);
		if (ql <= l && r <= qr) return sum[rt];
		int mid = l + r >> 1, ret = 0;
		if (ql <= mid) ret = (ret + query(lson, l, mid, ql, qr)) % P;
		if (mid + 1 <= qr) ret = (ret + query(rson, mid + 1, r, ql, qr)) % P;
		return ret;
	}
} tree;

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs1(int u, int from)
{
	siz[u] = 1;
	int mxsiz = 0, mxid = 0;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != from)
		{
			dep[v] = dep[u] + 1, fa[v] = u, siz[u] += siz[v];
			dfs1(v, u);
		}
		if (siz[v] > mxsiz) mxsiz = siz[v], mxid = v;
	}
	son[u] = mxid;
}

void dfs2(int u, int p)
{
	top[u] = p, tid[u] = ++dfn;
	if (son[u])
		dfs2(son[u], p);
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != fa[u] && v != son[u])
			dfs2(v, v);
	}
}

void init()
{
	n = read(), m = read(), R = read(), P = read();
	for (int i = 1; i <= n; i++)
		w[i] = read();
	for (int i = 1; i <= n - 1; i++)
		u = read(), v = read(), add(u, v), add(v, u);
	dfs1(R, 0);
	dfs2(R, R);
}

void solve()
{
	for (int i = 1; i <= n; i++)
		tree.insert(1, 1, n, tid[i], w[i]);
	while (m--)
	{
		int opt, x, y, z;
		opt = read();
		if (opt == 1)
		{
			x = read(), y = read(), z = read();
			while (top[x] != top[y])
			{
				if (dep[x] < dep[y]) swap(x, y);
				tree.plus(1, 1, n, tid[top[x]], tid[x], z);
				x = fa[top[x]];
			}
			if (dep[x] < dep[y]) swap(x, y);
			tree.plus(1, 1, n, tid[y], tid[x], z);
		}
		else if (opt == 2)
		{
			x = read(), y = read(), z = read();
			int ans = 0;
			while (top[x] != top[y])
			{
				if (dep[x] < dep[y]) swap(x, y);
				ans = (ans + tree.query(1, 1, n, tid[top[x]], tid[x])) % P;
				x = fa[top[x]];
			}
			if (dep[x] < dep[y]) swap(x, y);
			ans = (ans + tree.query(1, 1, n, tid[y], tid[x]));
		}
		else if (opt == 3)
		{
			x = read(), z = read();
			tree.plus(1, 1, n, tid[x], tid[x] + siz[x] - 1, z);
		}
		else
		{
			x = read();
			printf("%d\n", tree.query(1, 1, n, tid[x], tid[x] + siz[x] - 1));
		}
	}
}

int main()
{
	init();
	solve();
	return 0;
}
