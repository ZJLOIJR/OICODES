#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 5e5 + 7, INF = 666666;

int n, a;
struct segment { int left, right; } seg[N];

inline int min(int a, int b) { return a < b ? a : b; }

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
	int mi[N << 2];

	void init(int rt, int l, int r)
	{
		mi[rt] = INF;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		init(rt << 1, l, mid);
		init(rt << 1 | 1, mid + 1, r);
	}

	void insert(int rt, int l, int r, int po, int val)
	{
		if (l == r)
		{
			mi[rt] = min(mi[rt], val);
			return;
		}
		int mid = (l + r) >> 1;
		if (po <= mid) insert(rt << 1, l, mid, po, val);
		else insert(rt << 1 | 1, mid + 1, r, po, val);
		mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);
	}

	int qrymin(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && qr >= r) return mi[rt];
		int ret = INF, mid = (l + r) >> 1;
		if (ql <= mid) ret = min(ret, qrymin(rt << 1, l, mid, ql, qr));
		if (mid + 1 <= qr) ret = min(ret, qrymin(rt << 1 | 1, mid + 1, r, ql, qr));
		return ret;
	}
} Tree;

void init()
{
	n = read();
	for (int i = 1; i <= n; i++)
		a = read(), seg[i].left = i - a < 1 ? 1 : i - a, seg[i].right = i + a > n ? n : i + a;
	Tree.init(1, 0, n);
	Tree.insert(1, 0, n, 0, 0);
	sort(seg + 1, seg + n + 1, [](segment x, segment y)
			{
				return x.left < y.left;
			});
}

void solve()
{
	for (int i = 1; i <= n; i++)
		Tree.insert(1, 0, n, seg[i].right, Tree.qrymin(1, 0, n, seg[i].left - 1, seg[i].right) + 1);
	printf("%d\n", Tree.qrymin(1, 0, n, n, n));
}

int main()
{
	freopen("cat.in", "r", stdin);
	freopen("cat.out", "w", stdout);
	init();
	solve();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
