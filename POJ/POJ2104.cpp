#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 200007;

int n, q, l, r, k, len, tot = 0;

int root[N];
int a[N], b[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

struct SegTree
{
	int sum[N << 5], lson[N << 5], rson[N << 5];

	int qrysum(int &rt, int l, int r, int ql, int qr)
	{
		if (!rt)
			rt = ++tot;
		if (ql <= l && qr >= r)
			return sum[rt];
		int mid = (l + r) >> 1, ret = 0;
		if (ql <= mid)
			ret += qrysum(lson[rt], l, mid, ql, qr);
		if (mid + 1 <= qr)
			ret += qrysum(rson[rt], mid + 1, r, ql, qr);
		return ret;
	}

	void change(int &rt, int l, int r, int po)
	{
		if (!rt)
			rt = ++tot;
		if (l == r)
		{
			sum[rt]++;
			return;
		}
		int mid = (l + r) >> 1;
		if (po <= mid)
			change(lson[rt], l, mid, po);
		else
			change(rson[rt], mid + 1, r, po);
		sum[rt] = sum[lson[rt]] + sum[rson[rt]];
	}
} ST;

void insert(int p, int po)
{
	for (; po <= len; po += po & (-po))
		ST.change(root[po], 1, n, p);
}

int query(int ql, int qr, int po)
{
	int ret = 0;
	for (; po; po -= po & (-po))
		ret += ST.qrysum(root[po], 1, n, ql, qr);
	return ret;
}

void init()
{
	//freopen("IN", "r", stdin);
	n = read(), q = read();
	for (int i = 1; i <= n; i++)
		*(a + i) = read();
	memcpy(b, a, sizeof(a));
	sort(b + 1, b + n + 1);
	len = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++)
		insert(i, lower_bound(b + 1, b + len + 1, a[i]) - b);
}

int qrykth(int ql, int qr, int po)
{
	int l = 1, r = len, ans;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (query(ql, qr, mid) >= po)
			l = mid + 1, ans = mid;
		else
			r = mid - 1;
	}
	return ans;
}

void solve()
{
	while (q--)
	{
		l = read(), r = read(), k = read();
		printf("%d\n", b[qrykth(l, r, k)]);
	}
}

int main()
{
	init();
	solve();
	return 0;
}
