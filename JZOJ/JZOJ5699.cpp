#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5 + 3;
inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int lowbit(int x) { return x & (-x); }

int n, m, q, u, v, t, x, w, a[N];

int tot = 0, cnt = 0, st[N], to[N << 1], nx[N << 1], dep[N], dfn[N], out[N];
inline void addedg(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u, int from)
{
	dfn[u] = ++cnt;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from) dep[to[i]] = dep[u] + 1, dfs(to[i], u);
	out[u] = cnt;
}

ll sum[N * 200];
int tot0 = 0, root[N], lson[N * 200], rson[N * 200];

void insert(int &rt, int l, int r, int po, ll val)
{
	if (!rt) rt = ++tot0;
	if (l == r) { sum[rt] += val; return; }
	int mid = l + r >> 1;
	if (po <= mid) insert(lson[rt], l, mid, po, val);
	else insert(rson[rt], mid + 1, r, po, val);
	sum[rt] = sum[lson[rt]] + sum[rson[rt]];
}
ll qrysum(int rt, int l, int r, int ql, int qr)
{
	if (!rt) return 0;
	if (ql <= l && r <= qr) return sum[rt];
	int mid = l + r >> 1; ll ret = 0;
	if (ql <= mid) ret += qrysum(lson[rt], l, mid, ql, qr);
	if (mid + 1 <= qr) ret += qrysum(rson[rt], mid + 1, r, ql, qr);
	return ret;
}

void add(int po, int p, ll val)
{
	for (; po <= n; po += lowbit(po))
		insert(root[po], 1, 2 * n, p, val);
}
ll query(int po, int l, int r)
{
	ll ret = 0;
	if (!po) return 0;
	for (; po; po -= lowbit(po)) ret += qrysum(root[po], 1, 2 * n, l, r);
	return ret;
}

struct ques { int typ, x, t, w, id; } qry[N << 1];
ll ans[N];
int cmp(ques a, ques b) { return a.t == b.t ? a.typ < b.typ : a.t < b.t; }
int main()
{
	freopen("appletree.in", "r", stdin);
	freopen("appletree.out", "w", stdout);

	n = read(), m = read(), q = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n - 1; i++) u = read(), v = read(), addedg(u, v), addedg(v, u);
	dep[1] = 1, dfs(1, 0);
	for (int i = 1; i <= n; i++) add(dfn[i], dep[i], a[i]);
	for (int i = 1; i <= m; i++) qry[i].t = read(), qry[i].x = read(), qry[i].w = read(), qry[i].typ = 1;
	for (int i = 1; i <= q; i++) qry[i + m].t = read(), qry[i + m].x = read(), qry[i + m].id = i;
	sort(qry + 1, qry + m + q + 1, cmp);
	for (int i = 1; i <= m + q; i++)
		if (qry[i].typ) add(dfn[qry[i].x], dep[qry[i].x] + qry[i].t, qry[i].w);
		else ans[qry[i].id] = query(out[qry[i].x], dep[qry[i].x] + qry[i].t - 1, 2 * n) - 
							  query(dfn[qry[i].x] - 1, dep[qry[i].x] + qry[i].t - 1, 2 * n);
	for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
