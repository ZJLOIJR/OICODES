#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e5 + 3, M = 1e6 + 7;

int n, tot = 0, root, ans = 0, f[N];
struct range { int l, r; } a[N];
int cmp(range x, range y) { return x.r == y.r ? x.l < y.l : x.r > y.r; }
inline int max(int a, int b) { return a > b ? a : b; }

struct SegmentTree
{
	int mx[M << 1], lson[M << 1], rson[M << 1];
	void insert(int &rt, int l, int r, int po, int val)
	{
		if (!rt) rt = ++tot;
		if (l == r) { mx[rt] = max(mx[rt], val); return; }
		int mid = l + r >> 1;
		if (po <= mid) insert(lson[rt], l, mid, po, val);
		else insert(rson[rt], mid + 1, r, po, val);
		mx[rt] = max(mx[lson[rt]], mx[rson[rt]]);
	}
	int qrymax(int rt, int l, int r, int ql, int qr)
	{
		if (!rt) return 0;
		if (ql <= l && r <= qr) return mx[rt];
		int mid = l + r >> 1, ret = 0;
		if (ql <= mid) ret = max(ret, qrymax(lson[rt], l, mid, ql, qr));
		if (mid + 1 <= qr) ret = max(ret, qrymax(rson[rt], mid + 1, r, ql, qr));
		return ret;
	}
} tree;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++)
	{
		f[i] = tree.qrymax(root, 0, M - 7, 0, a[i].l) + 1;
		tree.insert(root, 0, M - 7, a[i].l, f[i]);
		ans = max(ans, f[i]);
	}
	printf("%d\n", ans);
	return 0;
}
