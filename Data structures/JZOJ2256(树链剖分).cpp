#pragma GCC optimize(2)
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 3e4 + 3, INF = 2147483647;

int n, m, u, v, tot = 0, dfn = 0;
int st[N], to[N << 1], nx[N << 1];
int w[N], siz[N], top[N], son[N], dep[N], fa[N], tid[N];
char str[10];

void swap(int &a, int &b) { int t = a; a = b, b = t; }
inline int max(int a, int b) { return a > b ? a : b; }
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
    int sum[N << 2], mx[N << 2];

    void insert(int rt, int l, int r, int po, int val)
    {
        if (l == r) { sum[rt] = mx[rt] = val; return; }
        int mid = l + r >> 1;
        if (po <= mid) insert(lson, l, mid, po, val);
        else insert(rson, mid + 1, r, po, val);
		sum[rt] = sum[lson] + sum[rson];
		mx[rt] = max(mx[lson], mx[rson]);
    }

    int query_max(int rt, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr) return mx[rt];
        int mid = l + r >> 1, ret = -INF;
        if (ql <= mid) ret = max(ret, query_max(lson, l, mid, ql, qr));
        if (mid + 1 <= qr) ret = max(ret, query_max(rson, mid + 1, r, ql, qr));
        return ret;
    }

	int query_sum(int rt, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr) return sum[rt];
        int mid = l + r >> 1, ret = 0;
        if (ql <= mid) ret = ret + query_sum(lson, l, mid, ql, qr);
        if (mid + 1 <= qr) ret = ret + query_sum(rson, mid + 1, r, ql, qr);
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
            dep[v] = dep[u] + 1, fa[v] = u;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > mxsiz) mxsiz = siz[v], mxid = v;
        }
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
    n = read();
    for (int i = 1; i <= n - 1; i++)
        u = read(), v = read(), add(u, v), add(v, u);
    for (int i = 1; i <= n; i++)
        w[i] = read();
    dfs1(1, 0);
    dfs2(1, 1);
}

void solve()
{
	m = read();
    for (int i = 1; i <= n; i++)
        tree.insert(1, 1, n, tid[i], w[i]);
    while (m--)
    {
		scanf("%s", str);
		if (str[0] == 'C')
		{
			int x = read(), y = read();
			tree.insert(1, 1, n, tid[x], y);
		}
		else if (str[1] == 'M')
		{
			int x = read(), y = read(), ans = -INF;
			while (top[x] != top[y])
            {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                ans = max(ans, tree.query_max(1, 1, n, tid[top[x]], tid[x]));
                x = fa[top[x]];
            }
			if (dep[x] < dep[y]) swap(x, y);
			ans = max(ans, tree.query_max(1, 1, n, tid[y], tid[x]));
			printf("%d\n", ans);
		}
		else if (str[1] == 'S')
		{
			int x = read(), y = read(), ans = 0;
			while (top[x] != top[y])
            {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                ans = ans + tree.query_sum(1, 1, n, tid[top[x]], tid[x]);
                x = fa[top[x]];
            }
			if (dep[x] < dep[y]) swap(x, y);
			ans = ans + tree.query_sum(1, 1, n, tid[y], tid[x]);
			printf("%d\n", ans);
		}
    }
}

int main()
{
    init();
    solve();
    return 0;
}
