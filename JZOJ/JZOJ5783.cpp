#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 3e5 + 7;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, q, opt, root, w[N];
int dfn, tid[N], out[N], dep[N], anc[N][18];

int tot, st[N], to[N << 1], nx[N << 1];
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

inline void dfs(int u)
{
	tid[u] = ++dfn;
	for (int i = st[u]; i; i = nx[i])
		if (!tid[to[i]])
		{
			dep[to[i]] = dep[u] + 1, anc[to[i]][0] = u;
			dfs(to[i]);
		}
	out[u] = dfn;
}

inline int getlca(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (register int i = 17; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	for (register int i = 17; i >= 0; i--) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

inline int lca(int u, int v, int rt)
{
	int ret = getlca(u, v), mxdep = dep[ret], x;
	x = getlca(u, rt);
	if (dep[x] > mxdep) mxdep = dep[x], ret = x;
	x = getlca(v, rt);
	if (dep[x] > mxdep) mxdep = dep[x], ret = x;
	return ret;
}

#define lson rt << 1
#define rson rt << 1 | 1
ll sum[N << 2], inc[N << 2];
inline void down(int rt, int l, int r)
{
	if (!inc[rt]) return;
	if (l != r) inc[lson] += inc[rt], inc[rson] += inc[rt];
	sum[rt] += (r - l + 1) * inc[rt], inc[rt] = 0;
}
inline void insert(int rt, int l, int r, int po, int v)
{
	if (l == r) { sum[rt] = v; return; }
	int mid = l + r >> 1;
	if (po <= mid) insert(lson, l, mid, po, v);
	else insert(rson, mid + 1, r, po, v);
	sum[rt] = sum[lson] + sum[rson];
}
inline void change(int rt, int l, int r, int ql, int qr, int v)
{
	if (ql > qr) return;
	down(rt, l, r);
	if (ql <= l && r <= qr) { inc[rt] += v; return; }
	int mid = l + r >> 1;
	if (ql <= mid) change(lson, l, mid, ql, qr, v);
	if (mid + 1 <= qr) change(rson, mid + 1, r, ql, qr, v);
	down(lson, l, mid), down(rson, mid + 1, r);
	sum[rt] = sum[lson] + sum[rson];
}
inline ll qrysum(int rt, int l, int r, int ql, int qr)
{
	if (ql > qr) return 0;
	down(rt, l, r);
	if (ql <= l && r <= qr) return sum[rt];
	int mid = l + r >> 1; ll ret = 0;
	if (ql <= mid) ret += qrysum(lson, l, mid, ql, qr);
	if (mid + 1 <= qr) ret += qrysum(rson, mid + 1, r, ql, qr);
	return ret;
}

int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);

	n = read(), q = read();
	for (int i = 1; i <= n; i++) w[i] = read();
	for (int i = 1, u, v; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	dep[1] = 1, dfs(1);
	for (int j = 1; j <= 17; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	for (int i = 1; i <= n; i++) insert(1, 1, n, tid[i], w[i]);
	root = 1;
	while (q--)
	{
		int opt = read();
		if (opt == 1) root = read();
		else if (opt == 2)
		{
			int u = read(), v = read(), x = read(), p = lca(u, v, root);
			if (p == root) change(1, 1, n, 1, n, x);
			else if (tid[p] <= tid[root] && out[root] <= out[p])
			{
				int now = root;
				for (register int i = 17; i >= 0; i--) if (dep[anc[now][i]] > dep[p]) now = anc[now][i];
				change(1, 1, n, 1, tid[now] - 1, x);
				change(1, 1, n, out[now] + 1, n, x);
			}
			else change(1, 1, n, tid[p], out[p], x);
		}
		else
		{
			int p = read();
			if (p == root) printf("%lld\n", qrysum(1, 1, n, 1, n));
			else if (tid[p] <= tid[root] && out[root] <= out[p])
			{
				int now = root;
				for (register int i = 17; i >= 0; i--) if (dep[anc[now][i]] > dep[p]) now = anc[now][i];
				printf("%lld\n", qrysum(1, 1, n, 1, n) - qrysum(1, 1, n, tid[now], out[now]));
			}
			else printf("%lld\n", qrysum(1, 1, n, tid[p], out[p]));
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
