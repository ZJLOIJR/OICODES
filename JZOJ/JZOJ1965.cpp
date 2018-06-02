#include <cstdio>
#include <cstring>
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 1e5 + 7;

struct SegmentTree
{
	int sum[N << 2], tag[N << 2];
	void down(int rt, int l, int r)
	{
		if (!tag[rt]) return;
		if (l != r) tag[lson] ^= 1, tag[rson] ^= 1;
		sum[rt] = r - l + 1 - sum[rt], tag[rt] = 0;
	}
	void change(int rt, int l, int r, int ql, int qr)
	{
		down(rt, l, r);
		if (ql <= l && r <= qr) { tag[rt] ^= 1; return; }
		int mid = l + r >> 1;
		if (ql <= mid) change(lson, l, mid, ql, qr);
		if (mid + 1 <= qr) change(rson, mid + 1, r, ql, qr);
		down(lson, l, mid), down(rson, mid + 1, r);
		sum[rt] = sum[lson] + sum[rson];
	}
	int qrysum(int rt, int l, int r, int ql, int qr)
	{
		down(rt, l, r);
		if (ql <= l && r <= qr) return sum[rt];
		int mid = l + r >> 1, ret = 0;
		if (ql <= mid) ret += qrysum(lson, l, mid, ql, qr);
		if (mid + 1 <= qr) ret += qrysum(rson, mid + 1, r, ql, qr);
		return ret;
	}
} tree;

int n, m, opt, l, r;

int main()
{
	scanf("%d%d", &n, &m);
	while (m--)
	{
		scanf("%d%d%d", &opt, &l, &r);
		if (opt) printf("%d\n", tree.qrysum(1, 1, n, l, r));
		else tree.change(1, 1, n, l, r);
	}
	return 0;
}
