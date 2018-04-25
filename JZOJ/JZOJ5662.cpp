#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

typedef long long ll;
const int N = 2e5 + 3;
const ll P = 1e9 + 7;

int n, q, opt, x, tot = 0, root;
int son[N][2], fa[N], siz[N], id[N];
ll w[N], sum[N];

struct SegmentTree
{
	ll mtp[N << 2];
	void init(int rt, int l, int r)
	{
		mtp[rt] = 1; if (l == r) return;
		int mid = l + r >> 1;
		init(lson, l, mid), init(rson, mid + 1, r);
	}
	void change(int rt, int l, int r, int po, ll val)
	{
		if (l == r) { mtp[rt] = val % P; return; }
		int mid = l + r >> 1;
		if (po <= mid) change(lson, l, mid, po, val);
		else change(rson, mid + 1, r, po, val);
		mtp[rt] = mtp[lson] * mtp[rson] % P;
	}
	ll qrymtp(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return mtp[rt];
		int mid = l + r >> 1; ll ret = 1;
		if (ql <= mid) ret = ret * qrymtp(lson, l, mid, ql, qr) % P;
		if (mid + 1 <= qr) ret = ret * qrymtp(rson, mid + 1, r, ql, qr) % P;
		return ret % P;
	}
} tree;

void upd(int x)
{
	siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
	sum[x] = ((sum[son[x][0]] + sum[son[x][1]]) % P + w[x]) % P;
	tree.change(1, 1, n, id[x], sum[x]);
}
void rotate(int x, int k)
{
	x = son[x][k];
	if (!x) return;
	int y = fa[x], z = fa[y];
	k = (son[y][1] == x);
	son[y][k] = son[x][!k]; if (son[x][!k]) fa[son[x][!k]] = y;
	son[x][!k] = y, fa[y] = x;
	fa[x] = z; if (z) son[z][son[z][1] == y] = x;
	upd(y), upd(x);
}

void dfs(int u)
{
	if (!u) return;
	siz[u] = 1, sum[u] = w[u];
	dfs(son[u][0]);
	siz[u] += siz[son[u][0]], sum[u] = (sum[u] + sum[son[u][0]]) % P;
	id[u] = ++tot;
	dfs(son[u][1]);
	siz[u] += siz[son[u][1]], sum[u] = (sum[u] + sum[son[u][1]]) % P;
}

int main()
{
	freopen("splay.in", "r", stdin);
	freopen("splay.out", "w", stdout);
	
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%d%d", w + i, &son[i][0], &son[i][1]);
		fa[son[i][0]] = fa[son[i][1]] = i;
	}
	for (int i = 1; i <= n; i++) if (!fa[i]) { root = i; break; }
	dfs(root);
	tree.init(1, 1, n);
	for (int i = 1; i <= n; i++) tree.change(1, 1, n, id[i], sum[i]);
	while (q--)
	{
		scanf("%d%d", &opt, &x);
		if (opt == 0 || opt == 1) rotate(x, opt);
		else printf("%lld\n", tree.qrymtp(1, 1, n, id[x] - siz[son[x][0]], id[x] + siz[son[x][1]]));
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
