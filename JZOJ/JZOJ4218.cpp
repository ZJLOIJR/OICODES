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
inline double sqr(double x) { return x * x; }
inline double getdis(double xx, double yy, double x_, double y_) { return sqrt(sqr(xx - x_) + sqr(yy - y_)); }
inline int lowbit(int x) { return x & (-x); }

const int N = 2e5 + 7;

int n, m, ax, ay, bx, by, len1, len2;
double dis1[N], dis2[N], arr1[N], arr2[N];

int tot = 0, root[N], lson[N * 100], rson[N * 100], sum[N * 100];
void add(int &rt, int l, int r, int po)
{
	if (!rt) rt = ++tot;
	if (l == r) { sum[rt]++; return; }
	int mid = l + r >> 1;
	if (po <= mid) add(lson[rt], l, mid, po);
	else add(rson[rt], mid + 1, r, po);
	sum[rt] = sum[lson[rt]] + sum[rson[rt]];
}
int get(int rt, int l, int r, int ql, int qr)
{
	if (!rt) return 0;
	if (ql <= l && r <= qr) return sum[rt];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += get(lson[rt], l, mid, ql, qr);
	if (mid + 1 <= qr) ret += get(rson[rt], mid + 1, r, ql, qr);
	return ret;
}
void insert(int x, int y)
{
	for (; x <= len1; x += lowbit(x)) add(root[x], 1, len2, y);
}
int query(int xx, int yy, int y_)
{
	int ret = 0;
	for (; xx; xx -= lowbit(xx)) ret += get(root[xx], 1, len2, yy, y_);
	return ret;
}

int main()
{
	n = read(), m = read(), ax = read(), ay = read(), bx = read(), by = read();
	for (int i = 1, x, y; i <= n; i++)
		x = read(), y = read(), dis1[i] = getdis(x, y, ax, ay), dis2[i] = getdis(x, y, bx, by);
	memcpy(arr1, dis1, sizeof(dis1));
	memcpy(arr2, dis2, sizeof(dis2));
	sort(arr1 + 1, arr1 + n + 1);
	sort(arr2 + 1, arr2 + n + 1);
	len1 = unique(arr1 + 1, arr1 + n + 1) - arr1 - 1;
	len2 = unique(arr2 + 1, arr2 + n + 1) - arr2 - 1;
	for (int i = 1; i <= n; i++) dis1[i] = lower_bound(arr1 + 1, arr1 + len1 + 1, dis1[i]) - arr1;
	for (int i = 1; i <= n; i++) dis2[i] = lower_bound(arr2 + 1, arr2 + len2 + 1, dis2[i]) - arr2;
	for (int i = 1; i <= n; i++) insert(dis1[i], dis2[i]);
	while (m--)
	{
		int r1 = read(), r2 = read(), ans = 0;
		if (r1 >= arr1[len1] || r2 >= arr2[len2]) { printf("%d\n", n); continue; }
		r1 = upper_bound(arr1 + 1, arr1 + len1 + 1, r1) - arr1;
		r2 = upper_bound(arr2 + 1, arr2 + len2 + 1, r2) - arr2;
		ans = query(len1, r2, len2) - query(r1 - 1, r2, len2);
		printf("%d\n", n - ans);
	}
	return 0;
}
