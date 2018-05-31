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
int query(int u, int v, int lca, int falca, int l, int r, int ql, int qr)
{
	if (ql > qr) return 0;
	if (ql <= l && r <= qr) return sum[u] + sum[v] - sum[lca] - sum[falca];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += query(lson[u], lson[v], lson[lca], lson[falca], l, mid, ql, qr);
	if (mid + 1 <= qr) ret += query(rson[u], rson[v], rson[lca], rson[falca], mid + 1, r, ql, qr);
	return ret;
}
int u, v, tot = 0, st[N], to[N << 1], nx[N << 1], anc[N][21], dep[N];
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u)
{
	insert(root[u], root[anc[u][0]], 1, m, a[u]);
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			dep[to[i]] = dep[u] + 1, anc[to[i]][0] = u, dfs(to[i]);
}
void lcapredo()
{
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
}
int getlca(int u, int v)
{
	if (dep[u] < dep[v]) u ^= v ^= u ^= v;
	for (int i = 20; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	for (int i = 20; i >= 0; i--) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

void init()
{
	n = read(), m = read(), q = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	dep[1] = 1, dfs(1);
	lcapredo();
}

void solve()
{
	while (q--)
	{
		int x = read() ^ lastans, y = read() ^ lastans, k = read() ^ lastans, ans = 0, lca;
		lastans = 0;
		lca = getlca(x, y);
		ans = query(root[x], root[y], root[lca], root[anc[lca][0]], 1, m, 1, k - 1);
		printf("%d ", ans), lastans ^= ans;
		ans = query(root[x], root[y], root[lca], root[anc[lca][0]], 1, m, k, k);
		printf("%d ", ans), lastans ^= ans;
		ans = query(root[x], root[y], root[lca], root[anc[lca][0]], 1, m, k + 1, m);
		printf("%d\n", ans), lastans ^= ans;
	}
}

int main()
{
	init();
	solve();
	return 0;
}
