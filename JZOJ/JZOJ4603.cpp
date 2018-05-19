#include <cmath>
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
inline int bit(int x) { return (1 << x); }
const int N = 1e5 + 7;

int n, c, m, l, r, w;
char ch;
struct SegmentTree
{
	int type[N << 2], col[N << 2];
	void down(int rt, int l, int r)
	{
		if (!col[rt]) return;
		if (l != r) col[lson] = col[rt], col[rson] = col[rt];
		type[rt] = bit(col[rt]), col[rt] = 0;
	}
	void change(int rt, int l, int r, int ql, int qr, int k)
	{
		down(rt, l, r);
		if (ql <= l && r <= qr) { col[rt] = k; return; }
		int mid = l + r >> 1;
		if (ql <= mid) change(lson, l, mid, ql, qr, k);
		if (mid + 1 <= qr) change(rson, mid + 1, r, ql, qr, k);
		down(lson, l, mid), down(rson, mid + 1, r);
		type[rt] = type[lson] | type[rson];
	}
	int query(int rt, int l, int r, int ql, int qr)
	{
		down(rt, l, r);
		if (ql <= l && r <= qr) return type[rt];
		int mid = l + r >> 1, ret = 0;
		if (ql <= mid) ret |= query(lson, l, mid, ql, qr);
		if (mid + 1 <= qr) ret |= query(rson, mid + 1, r, ql, qr);
		return ret;
	}
} tree;

int main()
{
	n = read(), c = read(), m = read();
	tree.change(1, 1, n, 1, n, 1);
	while (m--)
	{
		scanf(" %c", &ch), l = read(), r = read();
		if (l > r) { int t = l; l = r, r = t; }
		if (ch == 'C') w = read(), tree.change(1, 1, n, l, r, w);
		else
		{
			int sum = tree.query(1, 1, n, l, r), ans = 0;
			while (sum) ans += (sum & 1), sum >>= 1;
			printf("%d\n", ans);
		}
	}
	return 0;
}
