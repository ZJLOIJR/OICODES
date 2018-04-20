#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 2e5 + 3, M = 2e5 + 3;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m, a, b, x, l, r, tot = 0, ans;
int root[N], lson[M * 20], rson[M * 20], sum[M * 20];
void insert(int& rt, int fa, int l, int r, int po)
{
	if (!rt) rt = ++tot;
	sum[rt] = sum[fa] + 1;
	if (l == r) return;
	int mid = l + r >> 1;
	if (po <= mid) rson[rt] = rson[fa], insert(lson[rt], lson[fa], l, mid, po);
	else lson[rt] = lson[fa], insert(rson[rt], rson[fa], mid + 1, r, po);
}
int qry(int rt, int fa, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) return sum[rt] - sum[fa];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += qry(lson[rt], lson[fa], l, mid, ql, qr);
	if (mid + 1 <= qr) ret += qry(rson[rt], rson[fa], mid + 1, r, ql, qr);
	return ret;
}

int qrysum(int rt, int fa, int ql, int qr)
{
	ql = max(ql, 0), qr = max(qr, 0), qr = min(qr, M - 3);
	return qry(rt, fa, 0, M - 3, ql, qr);
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a = read(), insert(root[i], root[i - 1], 0, M - 3, a);
	while (m--)
	{
		b = read(), x = read(), l = read(), r = read(), ans = 0;
		for (int i = 17; i >= 0; i--)
		{
			int lower = ans + ((((b >> i) & 1) ^ 1) << i), upper = lower + (1 << i) - 1;
			if (qrysum(root[r], root[l - 1], lower - x, upper - x) > 0) ans = lower;
			else ans += ((b >> i) & 1) << i;
		}
		printf("%d\n", ans ^ b);
	}
	return 0;
}
