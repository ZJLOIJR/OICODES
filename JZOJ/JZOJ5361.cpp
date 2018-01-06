#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 5e5 + 7;

int n, a;
int left[N], right[N];

inline int max(int a, int b) { return a > b ? a : b; }

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

struct SegmentTree
{
	int mx[N];

	void insert(int rt, int l, int r, int po, int val)
	{
		if (l == r)
		{
			mx[rt] = val;
			return;
		}
		int mid = (l + r) >> 1;
		if (po <= mid) insert(rt << 1, l, mid, po, val);
		else insert(rt << 1 | 1, mid + 1, r, po, val);
		mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
	}

	int qrymax(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && qr >= r) return mx[rt];
		int ret = 0, mid = (l + r) >> 1;
		if (ql <= mid) ret = max(ret, qrymax(rt << 1, l, mid, ql, qr));
		if (mid + 1 <= qr) ret = max(ret, qrymax(rt << 1 | 1, mid + 1, r, ql, qr));
		return ret;
	}
} Tree;

void init()
{
	n = read();
	for (int i = 1; i <= n; i++)
		a = read(), 
}

int main()
{
	init();
	solve();
	return 0;
}
