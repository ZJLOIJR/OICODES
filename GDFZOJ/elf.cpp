#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1e5 + 7;
const ll P = 201314;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, q;

int dfn, fa[N], tid[N], son[N], top[N], size[N], dep[N];
int tot, st[N], to[N], nx[N];

struct note { int val, id, z; };
vector<note> notes[N];
ll ans[N];

void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs1(int u)
{
	int mxsiz = 0;
	size[u] = 1;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u])
		{
			dep[to[i]] = dep[u] + 1, fa[to[i]] = u, dfs1(to[i]), size[u] += size[to[i]];
			if (size[to[i]] > mxsiz) mxsiz = size[to[i]], son[u] = to[i];
		}
}

void dfs2(int u, int tp)
{
	tid[u] = ++dfn, top[u] = tp;
	if (son[u]) dfs2(son[u], tp);
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u] && to[i] != son[u])
			dfs2(to[i], to[i]);
}

#define lson rt << 1
#define rson rt << 1 | 1
ll sum[N << 2], inc[N << 2];
void down(int rt, int l, int r)
{
	if (!inc[rt]) return;
	if (l != r) inc[lson] += inc[rt], inc[rson] += inc[rt];
	sum[rt] += (r - l + 1) * inc[rt] % P, inc[rt] = 0;
}
void change(int rt, int l, int r, int ql, int qr)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) { inc[rt]++; return; }
	int mid = l + r >> 1;
	if (ql <= mid) change(lson, l, mid, ql, qr);
	if (mid + 1 <= qr) change(rson, mid + 1, r, ql, qr);
	down(lson, l, mid), down(rson, mid + 1, r);
	sum[rt] = sum[lson] + sum[rson];
}
ll qrysum(int rt, int l, int r, int ql, int qr)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) return sum[rt];
	int mid = l + r >> 1; ll ret = 0;
	if (ql <= mid) ret += qrysum(lson, l, mid, ql, qr);
	if (mid + 1 <= qr) ret += qrysum(rson, mid + 1, r, ql, qr);
	return ret;
}
void pathplus(int u, int v)
{
	while (top[u] != top[v])
	{
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		change(1, 1, n, tid[top[u]], tid[u]);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	change(1, 1, n, tid[v], tid[u]);
}
ll pathsum(int u, int v)
{
	ll ret = 0;
	while (top[u] != top[v])
	{
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ret += qrysum(1, 1, n, tid[top[u]], tid[u]);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	ret += qrysum(1, 1, n, tid[v], tid[u]);
	return ret;
}

int main()
{
	n = read(), q = read();
	for (int i = 2, x; i <= n; i++) x = read(), add(x, i);
	dep[1] = 1, dfs1(1);
	dfs2(1, 1);
	for (int i = 1, l, r, z; i <= q; i++)
	{
		l = read(), r = read(), z = read();
		notes[l - 1].push_back((note){-1, i, z});
		notes[r].push_back((note){1, i, z});
	}
	for (int i = 1; i <= n; i++)
	{
		pathplus(1, i);
		int siz = notes[i].size();
		for (int j = 0; j < siz; j++) ans[notes[i][j].id] += notes[i][j].val * pathsum(1, notes[i][j].z);
	}
	for (int i = 1; i <= q; i++) printf("%d\n", (int)(ans[i] % P));
	return 0;
}
