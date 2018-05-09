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

int tot = 0, cnt = 0, st[N], to[N << 1], nx[N << 1], dep[N], dfn[N], siz[N];
inline void addedg(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u, int from)
{
	dfn[u] = ++cnt, siz[u] = 1;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
			dep[to[i]] = dep[u] + 1, dfs(to[i], u), siz[u] += siz[to[i]];
}

ll sum[N * 50];
int tot0 = 0, root[N << 1], lson[N * 50], rson[N * 50];

void insert(int &rt, int l, int r, int po, ll val)
{
	if (!rt) rt = ++tot0;
	if (l == r) { sum[rt] = val; return; }
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
	for (; po <= 2 * n; po += lowbit(po))
		insert(root[po], 1, 2 * n, p, val);
}
ll query(int po, int l, int r)
{
	ll ret = 0;
	if (!po) return 0;
	for (; po; po -= lowbit(po)) ret += qrysum(root[po], 1, 2 * n, l, r);
}

int main()
{
	//freopen("appletree.in", "r", stdin);
	//freopen("appletree.out", "w", stdout);

	n = read(), m = read(), q = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n - 1; i++) u = read(), v = read(), addedg(u, v), addedg(v, u);
	dep[1] = 1, dfs(1, 0);
	for (int i = 1; i <= n; i++) add(i, 0, a[i]);
	for (int i = 1; i <= m; i++) t = read(), x = read(), w = read(), add(x, t + 1, w);
	while (q--)
	{
		t = read(), x = read();
		printf("%lld\n", query(dfn[x] + siz[x] - 1, dep[x] + t - 1, 2 * n) - query(dfn[x], dep[x] + t - 1, 2 * n));
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
