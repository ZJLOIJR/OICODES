#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 1e5 + 3;
typedef long long ll;

char ch;
int n, m, l, r;
int a[N];

inline void read(int& num)
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	num = f ? -x : x;
}

struct SegmentTree
{
	ll sum[N << 2];

	void set(int rt, int l, int r, int po, ll val)
	{
		if (l == r) { sum[rt] = val; return; }
		int mid = l + r >> 1;
		if (po <= mid) set(lson, l, mid, po, val);
		else set(rson, mid + 1, r, po, val);
		sum[rt] = sum[lson] + sum[rson];
	}

	ll qrysum(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return sum[rt];
		int mid = l + r >> 1; ll ret = 0;
		if (ql <= mid) ret += qrysum(lson, l, mid, ql, qr);
		if (mid + 1 <= qr) ret += qrysum(rson, mid + 1, r, ql, qr);
		return ret;
	}
} tree;

int main()
{
	read(n);
	for (int i = 1; i <= n; i++)
		read(m), tree.set(1, 1, n, i, m);
	read(m);
	while (m--)
	{
		scanf(" %c", &ch);
		if (ch == 'Q')
			read(l), read(r), printf("%lld\n", tree.qrysum(1, 1, n, l, r));
		else
			read(l), read(r), tree.set(1, 1, n, l, r);
	}
	return 0;
}