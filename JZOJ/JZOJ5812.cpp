#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

inline int min(int a, int b) { return a < b ? a : b; }
const int N = 1e5 + 7;

int n, a[N];
int cnt, ans[N][2];

struct note { int v, po; };
note mi[N << 2];
int inc[N << 2];
void down(int rt, int l, int r)
{
	if (!inc[rt]) return;
	if (l != r) inc[lson] += inc[rt], inc[rson] += inc[rt];
	mi[rt].v += inc[rt], inc[rt] = 0;
}
void upd(int rt, int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;
	down(lson, l, mid), down(rson, mid + 1, r);
	if (mi[lson].v < mi[rt].v) mi[rt] = mi[lson];
	if (mi[rson].v < mi[rt].v) mi[rt] = mi[rson];
}
void build(int rt, int l, int r)
{
	mi[rt].v = N;
	if (l == r)
	{
		mi[rt].v = a[l], mi[rt].po = l;
		return;
	}
	int mid = l + r >> 1;
	build(lson, l, mid), build(rson, mid + 1, r);
	upd(rt, l, r);
}
note qrymin(int rt, int l, int r, int ql, int qr)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) return mi[rt];
	int mid = l + r >> 1;
	note ret = (note){N, 0};
	if (ql <= mid)
	{
		note tmp = qrymin(lson, l, mid, ql, qr);
		if (tmp.v < ret.v) ret = tmp;
	}
	if (mid + 1 <= qr)
	{
		note tmp = qrymin(rson, mid + 1, r, ql, qr);
		if (tmp.v < ret.v) ret = tmp;
	}
	return ret;
}
void plus(int rt, int l, int r, int ql, int qr, int val)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) { inc[rt] += val; return; }
	int mid = l + r >> 1;
	if (ql <= mid) plus(lson, l, mid, ql, qr, val);
	if (mid + 1 <= qr) plus(rson, mid + 1, r, ql, qr, val);
	upd(rt, l, r);
}

void solve(int l, int r)
{
	if (l > r) return;
	note tmp = qrymin(1, 1, n, l, r);
	for (int i = 1; i <= tmp.v; i++) ans[++cnt][0] = l, ans[cnt][1] = r;
	plus(1, 1, n, l, r, -tmp.v);
	solve(l, tmp.po - 1), solve(tmp.po + 1, r);
}

int main()
{
	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	build(1, 1, n);
	solve(1, n);
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; i++) printf("%d %d\n", ans[i][0], ans[i][1]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
