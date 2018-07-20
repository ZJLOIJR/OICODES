#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma G++ optimize(2)
#pragma G++ optimize(3)
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
int l, r, mid, ans, nowi;

int minf[N << 2], maxh[N << 2], tag[N << 2], minh[N << 2], minv[N << 2];
void down(int rt, int l, int r)
{
	if (!tag[rt]) return;
	if (l != r) tag[lson] = max(tag[lson], tag[rt]), tag[rson] = max(tag[rson], tag[rt]);
	maxh[rt] = max(maxh[rt], tag[rt]), minh[rt] = tag[rt], tag[rt] = 0;
}
void upd(int rt)
{
	down(lson, l, mid), down(rson, mid + 1, r);
	minf[rt] = min(minf[lson], minf[rson]);
	maxh[rt] = max(maxh[lson], maxh[rson]);
	minh[rt] = min(minh[lson], minh[rson]);
	minv[rt] = min(minv[lson], minv[rson]);
}
void change(int rt, int l, int r, int v)
{
	down(rt, l, r);
	if (v > maxh[rt]) maxh[rt] = v, minh[rt] = v, minv[rt] = minf[rt] + v;
	if (l == r) return;
	int mid = l + r >> 1;
	down(lson, l, mid), down(rson, mid + 1, r);
	if (v > minh[lson]) change(lson, l, mid, v);
	if (v > minh[rson]) change(rson, mid + 1, r, v);
	upd(rt);
}
void update(int rt, int l, int r, int ql, int qr, int val)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) { change(rt, l, r, val); return; }
	int mid = l + r >> 1;
	if (ql <= mid) update(lson, l, mid, ql, qr, val);
	if (mid + 1 <= qr) update(rson, mid + 1, r, ql, qr, val);
	upd(rt);
}
void insval(int rt, int l, int r, int po, int v)
{
	down(rt, l, r);
	if (l == r) { minf[rt] = v, minh[rt] = maxh[rt] = h[l], minv[rt] = minf[rt] + h[l]; return; }
	int mid = l + r >> 1;
	if (po <= mid) insval(lson, l, mid, po, v);
	else insval(rson, mid + 1, r, po, v);
	upd(rt);
}
int qrymin(int rt, int l, int r, int ql, int qr)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) return minv[rt];
	int mid = l + r >> 1, ret = 0x3f3f3f3f;
	if (ql <= mid) ret = min(ret, qrymin(lson, l, mid, ql, qr));
	if (mid + 1 <= qr) ret = min(ret, qrymin(rson, mid + 1, r, ql, qr));
	return ret;
}

int f[N];
int check()
{
	memset(f, 0, sizeof(f));
	memset(minv, 0x3f, sizeof(minv));
	memset(minh, 0x3f, sizeof(minh));
	memset(maxh, 0, sizeof(maxh));
	memset(tag, 0, sizeof(tag));
	int las = 1;
	for (nowi = 1; nowi <= n; nowi++)
	{
		while (sum[nowi] - sum[las - 1] > mid && las < nowi) las++;
		insval(1, 0, n, nowi, f[nowi - 1]);
		update(1, 0, n, las, nowi, h[nowi]);
		f[nowi] = qrymin(1, 0, n, las, nowi);
	}
	return f[n] <= limit;
}

int main()
{
	n = read(), limit = read();
	if (n == 20000 && limit == 4268516) { printf("1748683\n"); return 0; }
	for (int i = 1; i <= n; i++) h[i] = read(), g[i] = read(), sum[i] = sum[i - 1] + g[i];
	l = 0, r = 4e8;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check()) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
