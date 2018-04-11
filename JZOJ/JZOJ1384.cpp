#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 2e5 + 5e4 + 3;

int n, m, l, r;
char str[N];

struct SegmentTree
{
	int inc[N << 2], sum[N << 2][10];

	void build(int rt, int l, int r)
	{
		if (l == r) { sum[rt][str[l] - '0']++; return; }
		int mid = l + r >> 1;
		build(lson, l, mid), build(rson, mid + 1, r);
		for (int i = 0; i < 10; i++) sum[rt][i] = sum[lson][i] + sum[rson][i];
	}

	void down(int rt, int l, int r)
	{
		if (inc[rt] == 0) return;
		if (l != r)
			inc[lson] += inc[rt], inc[rson] += inc[rt];
		int tmp[10];
		for (int i = 0; i < 10; i++) tmp[i] = sum[rt][i];
		for (int i = 0; i < 10; i++)
			sum[rt][i] = tmp[(i - inc[rt] + 100000 * 10) % 10];
		inc[rt] = 0;
	}

	int qrysum(int rt, int l, int r, int ql, int qr)
	{
		down(rt, l, r);
		if (ql <= l && r <= qr)
		{
			int ret = 0;
			for (int i = 0; i < 10; i++) ret += i * sum[rt][i];
			return ret;
		}
		int ret = 0, mid = l + r >> 1;
		if (ql <= mid) ret += qrysum(lson, l, mid, ql, qr);
		if (mid + 1 <= qr) ret += qrysum(rson, mid + 1, r, ql, qr);
		return ret;
	}

	void change(int rt, int l, int r, int ql, int qr)
	{
		down(rt, l, r);
		if (ql <= l && r <= qr) { inc[rt]++; return; }
		int mid = l + r >> 1;
		if (ql <= mid) change(lson, l, mid, ql, qr);
		if (mid + 1 <= qr) change(rson, mid + 1, r, ql, qr);
		down(lson, l, mid), down(rson, mid + 1, r);
		for (int i = 0; i < 10; i++) sum[rt][i] = sum[lson][i] + sum[rson][i];
	}
} tree;

int main()
{
	scanf("%d%d%s", &n, &m, str + 1);
	tree.build(1, 1, n);
	while (m--)
	{
		scanf("%d%d", &l, &r);
		printf("%d\n", tree.qrysum(1, 1, n, l, r));
		tree.change(1, 1, n, l, r);
	}
	return 0;
}
