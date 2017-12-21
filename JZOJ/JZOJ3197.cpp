#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 20009999;

int n, q, tot = 0;

int root[N / 100];

struct SegTree
{
	int sum[N], inc[N], lson[N], rson[N];

	void down(int rt, int l, int r)
	{
		if (inc[rt] == 0) return;
		if (l != r)
		{
			inc[lson[rt]] += inc[rt];
			inc[rson[rt]] += inc[rt];
		}
		sum[rt] += inc[rt];
		inc[rt] = 0;
	}
	
	void change(int &rt, int l, int r, int ql, int qr)
	{
		if (!rt)
			rt = ++tot;
		down(rt, l, r);
		if (ql <= l && qr >= r)
		{
			inc[rt]++;
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid)
			change(lson[rt], l, mid, ql, qr);
		if (mid + 1 <= qr)
			change(rson[rt], mid + 1, r, ql, qr);
		down(lson[rt], l, mid);
		down(rson[rt], mid + 1, r);
		sum[rt] = sum[lson[rt]] + sum[rson[rt]];
	}

	int qrysum(int &rt, int l, int r, int ql, int qr)
	{
		if (!rt)
			rt = ++tot;
		down(rt, l, r);
		if (ql <= l && qr >= r)
			return sum[rt];
		int mid = (l + r) >> 1, ret = 0;
		if (ql <= mid)
			ret += qrysum(lson[rt], l, mid, ql, qr);
		if (mid + 1 <= qr)
			ret += qrysum(rson[rt], mid + 1, r, ql, qr);
		return ret;
	}
} ST;

void insert(int rt, int l, int r, int ql, int qr, int po)
{
	ST.change(root[rt], l, r, ql, qr);
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	if (po <= mid)
		insert(rt << 1, l, mid, ql, qr, po);
	if (mid + 1 <= po)
		insert(rt << 1 | 1, mid + 1, r, ql, qr, po);
}

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int solve(int rt, int l, int r, int ql, int qr, int k)
{
	if (l == r)
		return l;
	int cnt = ST.qrysum(root[rt << 1 | 1], 1, n, ql, qr), mid = (l + r) >> 1;
	if (cnt < k)
		return solve(rt << 1, l, mid, ql, qr, k - cnt);
	else
		return solve(rt << 1 | 1, mid + 1, r, ql, qr, k);
}

int main()
{
	n = read(), q = read();
	int op, a, b, c;
	while (q--)
	{
		op = read(), a = read(), b = read(), c = read();
		if (op == 1)
			insert(1, 1, n, a, b, c);
		else
			printf("%d\n", solve(1, 1, n, a, b, c));
	}
	return 0;
}
