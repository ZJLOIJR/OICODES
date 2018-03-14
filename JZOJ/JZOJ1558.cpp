#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 4e5 + 3, LOW = 2e5 + 3;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, minn, add = 0, num, ans = 0;
char ch;

struct SegmentTree
{
	int sum[N << 2];

	void down(int rt, int l, int r)
	{
		if (l != r) sum[lson] = sum[rson] = 0;
	}

	void insert(int rt, int l, int r, int po)
	{
		if (l == r) { sum[rt]++; return; }
		if (!sum[rt]) down(rt, l, r);
		int mid = l + r >> 1;
		if (po <= mid) insert(lson, l, mid, po);
		else insert(rson, mid + 1, r, po);
		sum[rt] = sum[lson] + sum[rson];
	}

	int qrykth(int rt, int l, int r, int k)
	{
		if (!sum[rt]) down(rt, l, r);
		if (l == r) return l;
		int mid = l + r >> 1;
		if (sum[lson] >= k) return qrykth(lson, l, mid, k);
		else return qrykth(rson, mid + 1, r, k - sum[lson]);
	}

	void cover(int rt, int l, int r, int ql, int qr)
	{
		if (!sum[rt]) down(rt, l, r);
		if (ql <= l && r <= qr) { ans += sum[rt], sum[rt] = 0, down(rt, l, r); return; }
		int mid = l + r >> 1;
		if (ql <= mid) cover(lson, l, mid, ql, qr);
		if (mid + 1 <= qr) cover(rson, mid + 1, r, ql, qr);
		sum[rt] = sum[lson] + sum[rson];
	}
} tree;

int main()
{
	n = read(), minn = read();
	minn += LOW;
	while (n--)
	{
		ch = getchar(), num = read();
		switch (ch)
		{
			case 'I':
				if (num + LOW >= minn) tree.insert(1, 1, N, num + LOW - add);
				break;
			case 'A':
				add += num;
				break;
			case 'S':
				add -= num;
				tree.cover(1, 1, N, 1, minn - add - 1);
				break;
			case 'F':
				num = tree.sum[1] - num + 1;
				if (num < 1) printf("-1\n");
				else printf("%d\n", tree.qrykth(1, 1, N, num) + add - LOW);
				break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
