#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 1e5 + 3, INF = 0x3f3f3f3f;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m, k, d, a;
struct SegmentTree
{
	int sum[N << 2], lsum[N << 2][2], rsum[N << 2][2], dat[N << 2][2];

	void upd(int rt)
	{
		sum[rt] = sum[lson] + sum[rson];
		lsum[rt][0] = max(lsum[lson][0], sum[lson] + lsum[rson][0]);
		lsum[rt][1] = min(lsum[lson][1], sum[lson] + lsum[rson][1]);
		rsum[rt][0] = max(rsum[rson][0], sum[rson] + rsum[lson][0]);
		rsum[rt][1] = min(rsum[rson][1], sum[rson] + rsum[lson][1]);
		dat[rt][0] = max(rsum[lson][0] + lsum[rson][0], max(dat[lson][0], dat[rson][0]));
		dat[rt][1] = min(rsum[lson][1] + lsum[rson][1], min(dat[lson][1], dat[rson][1]));
	}

	void build(int rt, int l, int r)
	{
		lsum[rt][0] = rsum[rt][0] = dat[rt][0] = -INF;
		lsum[rt][1] = rsum[rt][1] = dat[rt][1] = INF;
		if (l == r) return;
		int mid = l + r >> 1;
		build(lson, l, mid), build(rson, mid + 1, r);
	}

	void change(int rt, int l, int r, int po, int val)
	{
		if (l == r)
		{
			sum[rt] = lsum[rt][0] = lsum[rt][1] = rsum[rt][0] = rsum[rt][1] = dat[rt][0] = dat[rt][1] = val;
			return;
		}
		int mid = l + r >> 1;
		if (po <= mid) change(lson, l, mid, po, val);
		else change(rson, mid + 1, r, po, val);
		upd(rt);
	}
} tree;

int main()
{
	n = read();
	tree.build(1, 1, n);
	for (int i = 1; i <= n; i++)
	{
		a = read();
		tree.change(1, 1, n, i, a);
	}
	m = read();
	while (m--)
	{
		k = read(), d = read();
		tree.change(1, 1, n, k, d);
		if (tree.dat[1][0] == tree.sum[1]) printf("%d\n", tree.sum[1] - tree.dat[1][1]);
		else printf("%d\n", max(tree.dat[1][0], tree.sum[1] - tree.dat[1][1]));
	}
	return 0;
}
