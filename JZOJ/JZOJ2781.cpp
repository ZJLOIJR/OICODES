#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

const int N = 5e4 + 7, M = 1e4 + 7;

int n, m;
int tot = 0, root[N], lson[M * 100], rson[M * 100], sum[M * 100];

void insert(int &rt, int fa, int l, int r, int po)
{
	if (!rt) rt = ++tot;
	sum[rt] = sum[fa] + 1;
	if (l == r) return;
	int mid = l + r >> 1;
	if (po <= mid) rson[rt] = rson[fa], insert(lson[rt], lson[fa], l, mid, po);
	else lson[rt] = lson[fa], insert(rson[rt], rson[fa], mid + 1, r, po);
}

int get(int rt, int fa, int l, int r, int ql, int qr)
{
	if (!rt) return 0;
	if (ql <= l && r <= qr) return sum[rt] - sum[fa];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += get(lson[rt], lson[fa], l, mid, ql, qr);
	if (mid + 1 <= qr) ret += get(rson[rt], rson[fa], mid + 1, r, ql, qr);
	return ret;
}
int query(int rt, int fa, int ql, int qr)
{
	if (qr > M - 7) qr = M - 7;
	return get(rt, fa, 0, M - 7, ql, qr);
}

int main()
{
	n = read(), m = read();
	for (int i = 1, a; i <= n; i++) a = read(), insert(root[i], root[i - 1], 0, M - 7, a);
	while (m--)
	{
		int l = read(), r = read(), b = read(), ret = 0;
		for (int i = 13; i >= 0; i--)
		{
			int u = ret + ((((b >> i) & 1) ^ 1) << i), v = u + (1 << i) - 1;
			if (query(root[r], root[l - 1], u, v)) ret = u;
			else ret += ((b >> i) & 1) << i;
		}
		printf("%lld\n", ret ^ b);
	}
	return 0;
}
