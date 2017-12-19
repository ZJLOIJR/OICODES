#include <cstdio>
#include <cstring>

const int N = 1000007;

inline int read();
void write(int x);
void init();
void solve();

int n, q;

int a[N];

struct ChairmanTree
{
	int rt[N], val[N << 5], lson[N << 5], rson[N << 5];
	int tot = 0;

	void prebuild(int &rt, int l, int r)
	{
		if (!rt)
			rt = ++tot;
		if (l == r)
		{
			val[rt] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		prebuild(lson[rt], l, mid);
		prebuild(rson[rt], mid + 1, r);
	}

	void build(int &rt, int fa, int l, int r, int po, int va)
	{
		if (!rt)
			rt = ++tot;
		if (l == r)
		{
			val[rt] = va;
			return;
		}
		int mid = (l + r) >> 1;
		if (po <= mid)
			rson[rt] = rson[fa], build(lson[rt], lson[fa], l, mid, po, va);
		if (mid + 1 <= po)
			lson[rt] = lson[fa], build(rson[rt], rson[fa], mid + 1, r, po, va);
	}

	int qry(int rt, int l, int r, int po)
	{
		if (l == r)
			return val[rt];
		int mid = (l + r) >> 1;
		if (po <= mid)
			return qry(lson[rt], l, mid, po);
		if (mid + 1 <= po)
			return qry(rson[rt], mid + 1, r, po);
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
	CT.prebuild(CT.rt[0], 1, n);
}

void solve()
{
	int a, b, c, d, cnt = 0;
	while (q--)
	{
		a = read(), b = read(), c = read();
		if (b == 1)
		{
			d = read();
			CT.build(CT.rt[++cnt], CT.rt[a], 1, n, c, d);
		}
		else
		{
			printf("%d\n", CT.qry(CT.rt[a], 1, n, c));
			CT.rt[++cnt] = CT.rt[a];
		}
	}
}
