#include <cstdio>
#include <cstring>

const int N = 50007, W = 1000007;

int n, q, l, r, tot = 0;

int las[W], root[N], a[N];

struct Tree
{
	int lson[N << 5], rson[N << 5], sum[N << 5];

	void insert(int &rt, int fa, int l, int r, int po, int val)
	{
		if (!rt)
			rt = ++tot;
		sum[rt] = sum[fa] + val;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		if (po <= mid)
			rson[rt] = rson[fa], insert(lson[rt], lson[fa], l, mid, po, val);
		else
			lson[rt] = lson[fa], insert(rson[rt], rson[fa], mid + 1, r, po, val);
	}

	int qrysum(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && qr >= r)
			return sum[rt];
		int mid = (l + r) >> 1, ret = 0;
		if (ql <= mid)
			ret += qrysum(lson[rt], l, mid, ql, qr);
		if (mid + 1 <= qr)
			ret += qrysum(rson[rt], mid + 1, r, ql, qr);
		return ret;
	}
} tree;

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
	n = read();
	for (int i = 1; i <= n; i++)
	{
		*(a + i) = read();
		if (!las[a[i]])
			tree.insert(root[i], root[i - 1], 1, n, i, 1);
		else
		{
			tree.insert(root[i], root[i - 1], 1, n, las[a[i]], -1);
			tree.insert(root[i], root[i], 1, n, i, 1);
		}
		las[a[i]] = i;
	}
}

void solve()
{
	q = read();
	while (q--)
	{
		l = read(), r = read();
		printf("%d\n", tree.qrysum(root[r], 1, n, l, r));
	}
}

int main()
{
	init();
	solve();
	return 0;
}
//莫队写法
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

const int N = 5e4 + 7, M = 2e5 + 7;

int n, m, tmp = 0, a[N], b[N];
int buc[1000007];
struct ques { int l, r, id; } q[M];
int ans[M];

int cmp(ques x, ques y) { return b[x.l] == b[y.l] ? x.r < y.r : x.l < y.l; }

void add(int po, int typ)
{
	buc[a[po]] += typ;
	if (typ == 1) tmp += (buc[a[po]] == 1);
	else tmp -= (buc[a[po]] == 0);
}

int main()
{
	n = read();
	int block = sqrt(n);
	for (int i = 1; i <= n; i++) a[i] = read(), b[i] = (i - 1) / block + 1;
	m = read();
	for (int i = 1; i <= m; i++) q[i].l = read(), q[i].r = read(), q[i].id = i;
	sort(q + 1, q + m + 1, cmp);
	for (int i = 1, l = 1, r = 0; i <= m; i++)
	{
		while (r > q[i].r) add(r, -1), r--;
		while (r < q[i].r) add(r + 1, 1), r++;
		while (l > q[i].l) add(l - 1, 1), l--;
		while (l < q[i].l) add(l, -1), l++;
		ans[q[i].id] = tmp;
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}
