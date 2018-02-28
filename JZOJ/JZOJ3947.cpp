#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;

const int K = 1e5 + 3;

int n, m, k, ans = 0, len;
struct point
{ int x, y, value; } a[K];
int yy[K], f[K];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int max(int a, int b) { return a > b ? a : b; }

struct SegmentTree
{
	int mx[K << 2];
	
	void insert(int rt, int l, int r, int po, int val)
	{
		if (l == r) { mx[rt] = max(mx[rt], val); return; }
		int mid = l + r >> 1;
		if (po <= mid) insert(lson, l, mid, po, val);
		else insert(rson, mid + 1, r, po, val);
		mx[rt] = max(mx[lson], mx[rson]);
	}

	int query(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return mx[rt];
		int mid = l + r >> 1, ret = 0;
		if (ql <= mid) ret = max(ret, query(lson, l, mid, ql, qr));
		if (mid + 1 <= qr) ret = max(ret, query(rson, mid + 1, r, ql, qr));
		return ret;
	}
} tree;

int main()
{
	n = read(), m = read(), k = read();
	for (int i = 1; i <= k; i++)
		a[i].x = read(), yy[i] = a[i].y = read(), a[i].value = read();
	sort(a + 1, a + k + 1, [](point u, point v){ return u.x == v.x ? u.y < v.y : u.x < v.x; });
	sort(yy + 1, yy + k + 1);
	len = unique(yy + 1, yy + k + 1) - yy - 1;
	for (int i = 1; i <= k; i++)
		a[i].y = lower_bound(yy + 1, yy + len + 1, a[i].y) - yy;
	for (int i = 1; i <= k; i++)
	{
		f[i] = tree.query(1, 1, len, 1, a[i].y) + a[i].value;
		tree.insert(1, 1, len, a[i].y, f[i]);
		ans = max(ans, f[i]);
	}
	printf("%d\n", ans);
	return 0;
}
