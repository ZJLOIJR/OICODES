#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

const int N = 270000, M = 140000;

int n, m, q, lastans, a[N];
int u, v, tot = 0, dfn = 0, st[N], to[N << 1], nx[N << 1], fa[N], dep[N], siz[N], tid[N], top[N], son[N], dfsorder[N];
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs1(int u)
{
	siz[u] = 1; int mxsiz = 0;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u])
		{
			int v = to[i];
			fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), siz[u] += siz[v];
			if (siz[v] > mxsiz) mxsiz = siz[v], son[u] = v;
		}
}
void dfs2(int u, int anc)
{
	tid[u] = ++dfn, dfsorder[dfn] = u, top[u] = anc;
	if (son[u]) dfs2(son[u], anc);
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u] && to[i] != son[u])
			dfs2(to[i], to[i]);
}

int cnt = 0, root[N], sum[N * 20], lson[N * 20], rson[N * 20];
void insert(int &rt, int fa, int l, int r, int po)
{
	if (!rt) rt = ++cnt;
	sum[rt] = sum[fa] + 1;
	if (l == r) return;
	int mid = l + r >> 1;
	if (po <= mid) rson[rt] = rson[fa], insert(lson[rt], lson[fa], l, mid, po);
	else lson[rt] = lson[fa], insert(rson[rt], rson[fa], mid + 1, r, po);
}
int query(int rt, int fa, int l, int r, int ql, int qr)
{
	if (!rt) return 0;
	if (ql <= l && r <= qr) return sum[rt] - sum[fa];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += query(lson[rt], lson[fa], l, mid, ql, qr);
	if (mid + 1 <= qr) ret += query(rson[rt], rson[fa], mid + 1, r, ql, qr);
	return ret;
}

void init()
{
	n = read(), m = read(), q = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	dep[1] = 1, dfs1(1), dfs2(1, 1);
	for (int i = 1; i <= n; i++) insert(root[i], root[i - 1], 1, m, a[dfsorder[i]]);
}

void solve()
{
	while (q--)
	{
		int tmpx = read(), tmpy = read(), k = read();
		tmpx ^= lastans, tmpy ^= lastans, k ^= lastans, lastans = 0;
		int x = tmpx, y = tmpy, ans = 0;
		while (top[x] != top[y])
		{
			if (dep[top[x]] < dep[top[y]]) x ^= y ^= x ^= y;
			ans += query(root[tid[x]], root[tid[top[x]]], 1, m, 1, k);
			x = fa[top[x]];
		}
		if (dep[x] < dep[y]) x ^= y ^= x ^= y;
		ans += query(root[tid[x]], root[tid[y]], 1, m, 1, k);
		printf("%d ", ans), lastans ^= ans;
		x = tmpx, y = tmpy, ans = 0;
		while (top[x] != top[y])
		{
			if (dep[top[x]] < dep[top[y]]) x ^= y ^= x ^= y;
			ans += query(root[tid[x]], root[tid[top[x]]], 1, m, k, k);
			x = fa[top[x]];
		}
		if (dep[x] < dep[y]) x ^= y ^= x ^= y;
		ans += query(root[tid[x]], root[tid[y]], 1, m, k, k);
		printf("%d ", ans), lastans ^= ans;
		x = tmpx, y = tmpy, ans = 0;
		while (top[x] != top[y])
		{
			if (dep[top[x]] < dep[top[y]]) x ^= y ^= x ^= y;
			ans += query(root[tid[x]], root[tid[top[x]]], 1, m, k, m);
			x = fa[top[x]];
		}
		if (dep[x] < dep[y]) x ^= y ^= x ^= y;
		ans += query(root[tid[x]], root[tid[y]], 1, m, k, m);
		printf("%d\n", ans), lastans ^= ans;
	}
}

int main()
{
	init();
	solve();
	return 0;
}
