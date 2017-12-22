#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100007;

int n, q, op, l, r, k, len;

int a[N], b[N];

struct Tree
{
	int rt[N], sum[N << 5], lson[N << 5], rson[N << 5];
	int tot = 0;

	void insert(int &rt, int fa, int l, int r, int po)
	{
		if (!rt)
			rt = ++tot;
		sum[rt] = sum[fa] + 1;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		if (po <= mid)
			rson[rt] = rson[fa], insert(lson[rt], lson[fa], l, mid, po);
		else
			lson[rt] = lson[fa], insert(rson[rt], rson[fa], mid + 1, po);
	}

	int qry(int rt, int fa, int l, int r, int k)
	{
		if (l == r)
			return l;
		int mid = (l + r) >> 1, cnt = sum[lson[rt]] - sum[lson[fa]];
		if (cnt >= k)
			return qry(lson[rt], lson[fa], l, mid, k);
		else
			return qry(rson[rt], rson[fa], mid + 1, r, k);
	}
} T;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

void init()
{
	n = read(), q = read();
	for (int i = 1; i <= n; i++)
		*(a + i) = read();
	memcpy(b, a, sizeof(a));
	sort(b + 1, b + n + 1);
	len = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++)
		T.insert(T.rt[i], T.rt[i - 1], 1, len, lower_bound(
}

int main()
{
	init();
	solve();
	return 0;
}
