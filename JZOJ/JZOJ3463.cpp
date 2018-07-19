#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

const int N = 2e4 + 7;

int n, limit, h[N], g[N], sum[N];
int l, r, mid, ans;

int val[N << 2], mx[N << 2], tag[N << 2], mi[N << 2];
void down(int rt, int l, int r)
{
	if (!tag[rt]) return;
	if (l != r) tag[lson] = max(tag[lson], tag[rt]), tag[rson] = max(tag[rson], tag[rt]);
	mx[rt] = max(mx[rt], tag[rt]), tag[rt] = 0;
}
int getmax(int rt, int l, int r, int po)
{
	down(rt, l, r);
	if (l == r) return mx[rt];
	int mid = l + r >> 1;
	if (po <= mid) return getmax(lson, l, mid, po);
	else return getmax(rson, mid + 1, r, po);
}
void update(int rt, int l, int r, int ql, int qr, int v)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) { tag[rt] = max(tag[rt], v); return; }
	int mid = l + r >> 1;
	if (ql <= mid) update(lson, l, mid, ql, qr, v);
	if (mid + 1 <= qr) update(rson, mid + 1, r, ql, qr, v);
	down(lson, l, mid), down(rson, mid + 1, r);
	mx[rt] = max(mx[lson], mx[rson]);
}
void insval(int rt, int l, int r, int po, int v)
{
	down(rt, l, r);
	if (l == r) { val[rt] = v, mi[rt] = val[rt] + getmax(1, 0, n, l + 1); return; }
	int mid = l + r >> 1;
	if (po <= mid) insval(lson, l, mid, po, v);
	else insval(rson, mid + 1, r, po, v);
	down(lson, l, mid), down(rson, mid + 1, r);
	mi[rt] = min(mi[lson], mi[rson]);
}
int qrymin(int rt, int l, int r, int ql, int qr)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) return mi[rt];
	int mid = l + r >> 1, ret = 0x3f3f3f3f;
	if (ql <= mid) ret = min(ret, qrymin(lson, l, mid, ql, qr));
	if (mid + 1 <= qr) ret = min(ret, qrymin(rson, mid + 1, r, ql, qr));
	return ret;
}

int f[N];
int check()
{
	memset(f, 0, sizeof(f));
	memset(val, 0, sizeof(val));
	memset(mx, 0, sizeof(mx));
	memset(tag, 0, sizeof(tag));
	memset(mi, 0x3f, sizeof(mi));
	insval(1, 0, n, 0, 0);
	int las = 1;
	for (int i = 1; i <= n; i++)
	{
		while (sum[i] - sum[las - 1] > mid && las < i) las++;
		f[i] = qrymin(1, 1, n, las, i);
		insval(1, 0, n, i, f[i]);
		update(1, 0, n, 1, i, h[i]);
	}
	return f[n] <= limit;
}

int main()
{
	freopen("input", "r", stdin);
	n = read(), limit = read();
	for (int i = 1; i <= n; i++) h[i] = read(), g[i] = read(), sum[i] = sum[i - 1] + g[i];
	l = 0, r = 1e9;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check()) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
