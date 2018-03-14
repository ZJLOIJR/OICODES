#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 1e5 + 3;

struct SegmentTree
{
	int sum[N << 2];
	
	void insert(int rt, int l, int r, int po)
	{
		if (l == r) { sum[rt]++; return; }
		int mid = l + r >> 1;
		if (po <= mid) insert(lson, l, mid, po);
		else insert(rson, mid + 1, r, po);
		sum[rt] = sum[lson] + sum[rson];
	}

	int qrysum(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return sum[rt];
		int mid = l + r >> 1, ret = 0;
		if (ql <= mid) ret += qrysum(lson, l, mid, ql, qr);
		if (mid + 1 <= qr) ret += qrysum(rson, mid + 1, r, ql, qr);
		return ret;
	}

	int qrykth(int rt, int l, int r, int k)
	{
		if (l == r) return l;
		int mid = l + r >> 1;
		if (sum[lson] > k) return qrykth(lson, l, mid, k);
		else return qrykth(rson, mid + 1, r, k - sum[lson]);
	}
} tree;
int n, minn, x, add = 0;
char opt;

int main()
{
	scanf("%d%d", &n, &minn);
	while (n--)
	{
		scanf(" %c%d", &opt, &x);
		if (opt == 'I')
			tree.insert(1, 1, N, x);
		else if (opt == 'A')
			add += x;
		else if (opt == 'S')
			add -= x;
		else
			printf("%d\n", tree.qrykth(1, minn, N, x) + add);
	}
	return 0;
}
