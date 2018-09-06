#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;

const int N = 1e2 + 7;

int n, len, maxy, Case;
double x1[N], y1[N], x2[N], y2[N], arry[N << 1], ans;
struct note { double x; int y1, y2, val; } a[N << 1];

int cmp(note p, note q) { return p.x < q.x; }

int cnt[N << 3]; double sum[N << 3];
void upd(int rt, int l, int r)
{
	if (cnt[rt]) { sum[rt] = arry[r + 1] - arry[l]; return; }
	if (l == r) sum[rt] = 0;
	else sum[rt] = sum[lson] + sum[rson];
}
void change(int rt, int l, int r, int ql, int qr, int val)
{
	if (ql <= l && r <= qr) { cnt[rt] += val, upd(rt, l, r); return; }
	int mid = l + r >> 1;
	if (ql <= mid) change(lson, l, mid, ql, qr, val);
	if (mid + 1 <= qr) change(rson, mid + 1, r, ql, qr, val);
	upd(rt, l, r);
}

int main()
{
	while (1)
	{
		scanf("%d", &n);
		if (!n) break;
		ans = 0;
		memset(sum, 0, sizeof(sum));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++)
		{
			scanf("%lf%lf%lf%lf", x1 + i, y1 + i, x2 + i, y2 + i);
			arry[++maxy] = y1[i], arry[++maxy] = y2[i];
		}
		sort(arry + 1, arry + maxy + 1);
		for (int i = 1; i <= n; i++)
		{
			int Y1 = lower_bound(arry + 1, arry + maxy + 1, y1[i]) - arry,
				Y2 = lower_bound(arry + 1, arry + maxy + 1, y2[i]) - arry;
			a[++len] = (note){x1[i], Y1, Y2, 1};
			a[++len] = (note){x2[i] + 1, Y1, Y2, -1};
		}
		sort(a + 1, a + len + 1, cmp);
		for (int i = 1; i <= len; i++)
		{
			change(1, 1, maxy, a[i].y1, a[i].y2, a[i].val);
			if (i != 1) ans += (a[i].x - a[i - 1].x) * sum[1];
		}
		printf("Test case #1\nTotal explored area: %.2lf\n", ans);
	}
	return 0;
}
