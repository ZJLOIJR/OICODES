#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100007;

int n, q, l, r, k, len, tot = 0;
int a[N], b[N];

inline int read();
void init();
void solve();

struct ChairmanTree
{
	int rt[N], sum[N << 5], lson[N << 5], rson[N << 5];
	
	void prebuild(int &rt, int l, int r)
	{
		if (!rt)
			rt = ++tot;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		prebuild(lson[rt], l, mid);
		prebuild(rson[rt], mid + 1, r);
	}

	void build(int &rt, int fa, int l, int r, int po)
	{
		if (!rt)
			rt = ++tot;
		sum[rt] = sum[fa] + 1;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		if (po <= mid)
			rson[rt] = rson[fa], build(lson[rt], lson[fa], l, mid, po);
		if (mid + 1 <= po)
			lson[rt] = lson[fa], build(rson[rt], rson[fa], mid + 1, r, po);
	}

	int qrykth(int rt, int fa, int l, int r, int po)
	{
		if (l == r)
			return l;
		int cnt = sum[lson[rt]] - sum[lson[fa]], mid = (l + r) >> 1;
		if (cnt >= po)
			return qrykth(lson[rt], lson[fa], l, mid, po);
		else
			return qrykth(rson[rt], rson[fa], mid + 1, r, po - cnt);
	}

} CT;

int main()
{
	init();
	solve();
	return 0;
}

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
	return x * f;
}

void init()
{
	n = read(), q = read();
	for (int i = 1; i <= n; i++)
		*(a + i) = read();
	memcpy(b, a, sizeof(a));
	sort(b + 1, b + n + 1);
	len = unique(b + 1, b + n + 1) - b - 1;
	CT.prebuild(CT.rt[0], 1, len);
	for (int i = 1; i <= n; i++)
		CT.build(CT.rt[i], CT.rt[i - 1], 1, len, lower_bound(b + 1, b + len + 1, a[i]) - b);
}

void solve()
{
	while (q--)
	{
		l = read(), r = read(), k = read();
		printf("%d\n", b[CT.qrykth(CT.rt[r], CT.rt[l - 1], 1, len, k)]);
	}
}
