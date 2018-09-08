#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;

typedef long long ll;
const int N = 1e4 + 7;
inline ll max(ll a, ll b) { return a > b ? a : b; }

ll ans;
int n, w, h, len, maxy, arr[N << 1];
struct note { int x, y1, y2, val; } a[N << 1];

ll mx[N << 3], inc[N << 3];
void down(int rt, int l, int r)
{
	if (!inc[rt]) return;
	if (l != r) inc[lson] += inc[rt], inc[rson] += inc[rt];
	mx[rt] += inc[rt], inc[rt] = 0;
}
void change(int rt, int l, int r, int ql, int qr, ll v)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) { inc[rt] += v; return; }
	int mid = l + r >> 1;
	if (ql <= mid) change(lson, l, mid, ql, qr, v);
	if (mid + 1 <= qr) change(rson, mid + 1, r, ql, qr, v);
	down(lson, l, mid), down(rson, mid + 1, r);
	mx[rt] = max(mx[lson], mx[rson]);
}
ll getmax(int rt, int l, int r, int ql, int qr)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) return mx[rt];
	int mid = l + r >> 1; ll ret = 0;
	if (ql <= mid) ret = max(ret, getmax(lson, l, mid, ql, qr));
	if (mid + 1 <= qr) ret = max(ret, getmax(rson, mid + 1, r, ql, qr));
	return ret;
}

int cmp(note a, note b) { return a.x < b.x; }

int main()
{
	scanf("%d%d%d", &n, &w, &h); w--, h--;
	for (int i = 1, x, y, z; i <= n; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		arr[++maxy] = y, arr[++maxy] = y + h;
		a[++len] = (note){x, y, y + h, z};
		a[++len] = (note){x + w + 1, y, y + h, -z};
	}
	sort(arr + 1, arr + maxy + 1);
	sort(a + 1, a + len + 1, cmp);
	for (int i = 1; i <= len; i++)
	{
		a[i].y1 = lower_bound(arr + 1, arr + maxy + 1, a[i].y1) - arr;
		a[i].y2 = lower_bound(arr + 1, arr + maxy + 1, a[i].y2) - arr;
		change(1, 1, maxy, a[i].y1, a[i].y2, a[i].val);
		ans = max(ans, getmax(1, 1, maxy, 1, maxy));
	}
	printf("%lld\n", ans);
	return 0;
}
