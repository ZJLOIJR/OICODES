#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 100007, H = 1000007;

int n, ans = 0, ret;
int a[N], f[N][2];

inline int max(int a, int b) { return a > b ? a : b; }

struct SegmentTree
{
	int mx[H << 2];

	void insert(int rt, int l, int r, int po, int val)
	{
		if (l == r) { mx[rt] = max(mx[rt], val); return; }
		int mid = l + r >> 1;
		if (po <= mid) insert(lson, l, mid, po, val);
		else insert(rson, mid + 1, r, po, val);
		mx[rt] = max(mx[lson], mx[rson]);
	}

	int qrymax(int rt, int l, int r, int ql, int qr)
	{
		if (ql > qr) return 0;
		if (ql <= l && r <= qr) { return mx[rt]; }
		int mid = l + r >> 1, ret = 0;
		if (ql <= mid) ret = max(ret, qrymax(lson, l, mid, ql, qr));
		if (mid + 1 <= qr) ret = max(ret, qrymax(rson, mid + 1, r, ql, qr));
		return ret;
	}
} tree0, tree1;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = tree1.qrymax(1, 0, H, a[i] + 1, H) + 1;
		tree0.insert(1, 0, H, a[i], f[i][0]);
		f[i][1] = tree0.qrymax(1, 0, H, 0, a[i] - 1) + 1;
		tree1.insert(1, 0, H, a[i], f[i][1]);
		ans = max(ans, max(f[i][0], f[i][1]));
	}
	printf("%d\n", ans);
	return 0;
}
