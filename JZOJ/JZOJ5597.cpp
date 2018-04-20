#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;

typedef long long ll;
const int N = 5e4 + 3, INF = 0x3f3f3f3f;

int n, q, len;
ll g, r, t, d[N], sum[N], arr[N], mo[N], f[N];

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

struct SegmentTree
{
	int mi[N << 2];
	void insert(int rt, int l, int r, int po, int val)
	{
		if (l == r) { mi[rt] = min(mi[rt], val); return; }
		int mid = l + r >> 1;
		if (po <= mid) insert(lson, l, mid, po, val);
		else insert(rson, mid + 1, r, po, val);
		mi[rt] = min(mi[lson], mi[rson]);
	}
	int qrymin(int rt, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return mi[rt];
		int mid = l + r >> 1, ret = INF;
		if (ql <= mid) ret = min(ret, qrymin(lson, l, mid, ql, qr));
		if (mid + 1 <= qr) ret = min(ret, qrymin(rson, mid + 1, r, ql, qr));
		return ret;
	}
} tree;

int main()
{
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);

	memset(tree.mi, 0x3f, sizeof(tree.mi));
	n = read(), g = read(), r = read();
	for (int i = 1; i <= n + 1; i++) d[i] = read(), sum[i] = sum[i - 1] + d[i], arr[i] = mo[i] = sum[i] % (g + r);
	arr[n + 2] = 0, arr[n + 3] = g + r;
	sort(arr + 1, arr + n + 4);
	len = unique(arr + 1, arr + n + 4) - arr - 1;
	for (int i = n; i >= 1; i--)
	{
		ll lval = (mo[i] + g) % (g + r), rval = (mo[i] + g + r - 1) % (g + r);
		int lx = lower_bound(arr + 1, arr + len + 1, lval) - arr,
			rx = upper_bound(arr + 1, arr + len + 1, rval) - arr - 1, tmp;
		if (lval <= rval) tmp = tree.qrymin(1, 1, len, lx, rx);
		else tmp = min(tree.qrymin(1, 1, len, lx, len), tree.qrymin(1, 1, len, 1, rx));
		if (tmp >= INF) f[i] = sum[n + 1] - sum[i];
		else f[i] = f[tmp] + sum[tmp] - sum[i] + g + r - (sum[tmp] - sum[i]) % (g + r);
		tree.insert(1, 1, len, lower_bound(arr + 1, arr + len + 1, mo[i]) - arr, i);
	}
	q = read();
	while (q--)
	{
		t = read();
		ll beg = (g + r - t % (g + r)) % (g + r);
		ll lval = (beg + g) % (g + r), rval = (beg + g + r - 1) % (g + r);
		int lx = lower_bound(arr + 1, arr + len + 1, lval) - arr,
			rx = upper_bound(arr + 1, arr + len + 1, rval) - arr - 1, tmp;
		if (lval <= rval) tmp = tree.qrymin(1, 1, len, lx, rx);
		else tmp = min(tree.qrymin(1, 1, len, lx, len), tree.qrymin(1, 1, len, 1, rx));
		if (tmp >= INF) printf("%lld\n", t + sum[n + 1]);
		else printf("%lld\n", t + sum[tmp] + g + r - (t + sum[tmp]) % (g + r) + f[tmp]);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
