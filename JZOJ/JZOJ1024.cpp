#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

const int N = 5e5 + 3;

int n, m, L, R, u, v, a[N], fa[N];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

struct SegmentTree
{
	int mi[N << 2], mx[N << 2];
	void build(int rt, int l, int r)
	{
		mx[rt] = 0, mi[rt] = 0x3f3f3f3f;
		if (l == r) { mi[rt] = mx[rt] = a[l]; return; }
		int mid = l + r >> 1;
		build(lson, l, mid), build(rson, mid + 1, r);
		mi[rt] = min(mi[lson], mi[rson]);
		mx[rt] = max(mx[lson], mx[rson]);
	}
	int qrymax(int rt, int l, int r)
	{
		if (L <= l && r <= R) return mx[rt];
		int mid = l + r >> 1, ret = 0;
		if (L <= mid) ret = max(ret, qrymax(lson, l, mid));
		if (mid + 1 <= R) ret = max(ret, qrymax(rson, mid + 1, r));
		return ret;
	}
	int qrymin(int rt, int l, int r)
	{
		if (L <= l && r <= R) return mi[rt];
		int mid = l + r >> 1, ret = 0x3f3f3f3f;
		if (L <= mid) ret = min(ret, qrymin(lson, l, mid));
		if (mid + 1 <= R) ret = min(ret, qrymin(rson, mid + 1, r));
		return ret;
	}
} sgt;


int main()
{
	while (~scanf("%d", &n))
	{
		for (int i = 1; i <= n; i++) scanf("%d", a + i), fa[i] = i;
		sgt.build(1, 1, n);
		scanf("%d", &m);
		while (m--)
		{
			scanf("%d%d", &L, &R);
			u = sgt.qrymin(1, 1, n), v = sgt.qrymax(1, 1, n);
			fa[getfa(v)] = getfa(u);
		}
		scanf("%d", &m);
		while (m--)
		{
			scanf("%d%d", &u, &v);
			printf(getfa(u) == getfa(v) ? "YES\n" : "NO\n");
		}
	}
	return 0;
}
