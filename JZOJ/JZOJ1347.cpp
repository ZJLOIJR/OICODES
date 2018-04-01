#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2e5 + 7, M = 1e6 + 1e5;

int n, ans = 0;
int a[N], f[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
struct SegmentTree
{
	int mx[(M << 2) + 50];

	int qrymax(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return mx[rt];
		int mid = l + r >> 1, ret = 0;
		if (ql <= mid) ret = max(ret, qrymax(rt << 1, l, mid, ql, qr));
		if (mid + 1 <= qr) ret = max(ret, qrymax(rt << 1 | 1, mid + 1, r, ql, qr));
		return ret;
	}

	void set(int rt, int l, int r, int po, int val)
	{
		if (l == r) { mx[rt] = max(mx[rt], val); return; }
		int mid = l + r >> 1;
		if (po <= mid) set(rt << 1, l, mid, po, val);
		else set(rt << 1 | 1, mid + 1, r, po, val);
		mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
	}
} tree;

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read(), a[i + n] = a[i];
	n *= 2;
	for (int i = 1; i <= n; i++)
	{
		f[i] = max(tree.qrymax(1, 0, M, 0, max(a[i] - 2, 0)), max(tree.qrymax(1, 0, M, min(a[i] + 2, M), M), tree.qrymax(1, 0, M, a[i], a[i]))) + 1;
		tree.set(1, 0, M, a[i], f[i]);
		ans = max(ans, f[i]);
	}
	printf("%d\n", ans / 2);
	return 0;
}
