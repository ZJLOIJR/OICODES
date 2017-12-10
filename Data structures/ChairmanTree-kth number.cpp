#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 200007;

int n, q, l, r, k, len, tot = 0;
int a[N], b[N];

struct ChairmanTree
{
	int rt[N], lson[N * 20], rson[N * 20], sum[N * 20];

	void prebuild(int& rt, int l, int r)
	{
		if (!rt)
			rt = ++tot;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		prebuild(lson[rt], l, mid);
		prebuild(rson[rt], mid + 1, r);
	}

	void build(int& rt, int fa, int l, int r, int po)
	{
		if (!rt)
			rt = ++tot;
		sum[rt] = sum[fa] + 1;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		if (po <= mid)
		{
			rson[rt] = rson[fa];
			build(lson[rt], lson[fa], l, mid, po);
		}
		if (mid + 1 <= po)
		{
			lson[rt] = lson[fa];
			build(rson[rt], rson[fa], mid + 1, r, po);
		}
	}

	int qrykth(int rt, int fa, int l, int r, int po)
	{
		if (l == r)
			return l;
		int cnt = sum[lson[rt]] - sum[lson[fa]], mid = (l + r) >> 1;
		if (cnt < po)
			return qrykth(rson[rt], rson[fa], mid + 1, r, po - cnt);
		else
			return qrykth(lson[rt], lson[fa], l, mid, po);
	}
} CT;

void init()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	memcpy(b, a, sizeof(a));
	
	sort(b + 1, b + n + 1);
	len = unique(b + 1, b + n + 1) - b - 1;
	
	CT.prebuild(CT.rt[0], 1, len);
	for (int i = 1; i <= n; i++)
		CT.build(CT.rt[i], CT.rt[i - 1], 1, n, lower_bound(b + 1, b + len + 1, a[i]) - b);
}

void solve()
{
	while (q--)
	{
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", b[CT.qrykth(CT.rt[r], CT.rt[l - 1], 1, n, k)]);
	}
}

int main()
{
	init();
	solve();
	return 0;
}
