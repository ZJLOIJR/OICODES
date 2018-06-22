#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

typedef long long ll;
const int N = 1e5 + 7;

ll sum[N << 2], inc[N << 2];
void down(int rt, int l, int r)
{
	if (!inc[rt]) return;
	if (l != r) inc[lson] += inc[rt], inc[rson] += inc[rt];
	sum[rt] += inc[rt] * (r - l + 1), inc[rt] = 0;
}
void plus(int rt, int l, int r, int ql, int qr, ll val)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) { inc[rt] += val; return; }
	int mid = l + r >> 1;
	if (ql <= mid) plus(lson, l, mid, ql, qr, val);
	if (mid + 1 <= qr) plus(rson, mid + 1, r, ql, qr, val);
	down(lson, l, mid), down(rson, mid + 1, r);
	sum[rt] = sum[lson] + sum[rson];
}
ll query(int rt, int l, int r, int ql, int qr)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) return sum[rt];
	int mid = l + r >> 1; ll ret = 0;
	if (ql <= mid) ret += query(lson, l, mid, ql, qr);
	if (mid + 1 <= qr) ret += query(rson, mid + 1, r, ql, qr);
	return ret;
}

int n, q, tot = 0;
int cnt = 0, st[N], to[N], nx[N], fa[N], dep[N], siz[N], son[N], top[N], tid[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs1(int u)
{
	int mxsiz = 0;
	siz[u] = 1;
	for (int i = st[u]; i; i = nx[i])
	{
		dep[to[i]] = dep[u] + 1, dfs1(to[i]), siz[u] += siz[to[i]];
		if (siz[to[i]] > mxsiz) son[u] = to[i];
	}
}

void dfs2(int u, int anc)
{
	tid[u] = ++cnt, top[u] = anc;
	if (son[u]) dfs2(son[u], anc);
	for (int i = st[u]; i; i = nx[i]) if (to[i] != son[u]) dfs2(to[i], to[i]);
}

void init()
{
	n = read();
	for (int i = 1, u, v; i < n; i++) u = read() + 1, v = read() + 1, add(u, v), fa[v] = u;
	dep[1] = 1, dfs1(1), dfs2(1, 1);
}

void solve()
{
	q = read();
	int u, v, d;
	char opt;
	while (q--)
	{
		scanf(" %c", &opt);
		if (opt == 'Q') u = read() + 1, printf("%lld\n", query(1, 1, n, tid[u], tid[u] + siz[u] - 1));
		else
		{
			u = read() + 1, v = read() + 1, d = read();
			while (top[u] != top[v])
			{
				if (dep[top[u]] < dep[top[v]]) u ^= v ^= u ^= v;
				plus(1, 1, n, tid[top[u]], tid[u], d);
				u = fa[top[u]];
			}
			if (dep[u] < dep[v]) u ^= v ^= u ^= v;
			plus(1, 1, n, tid[v], tid[u], d);
		}
	}
}

int main()
{
	init();
	solve();
	return 0;
}
