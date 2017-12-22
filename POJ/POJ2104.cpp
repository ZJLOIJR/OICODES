#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 100007;

int n, q, l, r, k, len;

int root[N];
int a[N], b[N], rak[N];

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
	int sum[N << 1], lson[N << 1], rson[N << 1];
	int tot = 0;

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
	for (; po <= n; po += po & (-po))
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
	freopen("IN", "r", stdin);
	n = read(), q = read();
	for (int i = 1; i <= n; i++)
		*(a + i) = read(), rak[i] = i;
	memcpy(b, a, sizeof(a));
	sort(b + 1, b + n + 1);
	sort(rak + 1, rak + n + 1, [](int x, int y){ return a[x] < a[y]; });
	len = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= len; i++)
		insert(lower_bound(a + 1, a + n + 1, b[i]) - a, i);
}

int qrykth(int l, int r, int ql, int qr, int po)
{
	if (l == r)
		return l;
	int mid = (l + r) >> 1, cnt = query(ql, qr, po - 1);
	if (cnt >= po)
		return qrykth(l, mid, ql, qr, po);
	else
		return qrykth(mid + 1, r, ql, qr, po - cnt);
}

void solve()
{
	while (q--)
	{
		l = read(), r = read(), k = read();
		printf("%d\n", qrykth(1, n, l, r, k));
	}
}

int main()
{
	init();
	solve();
	return 0;
}
