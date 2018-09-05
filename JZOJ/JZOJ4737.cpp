#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 6e5 + 7;

int l, r, mid, ans = -1;
int n, x[N], y[N];
struct note { int val, id; } a[N], b[N];
int ranka[N], rankb[N];
ll bucx[N], bucy[N], d;

int cmp(note p, note q) { return p.val < q.val; }

int check()
{
	memset(bucx, 0, sizeof(bucx));
	memset(bucy, 0, sizeof(bucy));
	ll ret = 0, s1 = 0, s2 = 0;
	for (int i = 1; i <= mid; i++) bucx[ranka[i]] += x[i], bucy[rankb[i]] += y[i];
	for (int i = 1; i <= n; i++) s2 += bucx[i];
	for (int i = 1, cnt = 0; i <= n; i++)
	{
		if (bucx[i] > 0) cnt++;
		s1 += bucx[i], s2 -= bucx[i];
		ret += (cnt * bucx[i] - s1) + (s2 - (mid - cnt) * bucx[i]);
	}
	s1 = s2 = 0;
	for (int i = 1; i <= n; i++) s2 += bucy[i];
	for (int i = 1, cnt = 0; i <= n; i++)
	{
		if (bucy[i] > 0) cnt++;
		s1 += bucy[i], s2 -= bucy[i];
		ret += (cnt * bucy[i] - s1) + (s2 - (mid - cnt) * bucy[i]);
	}
	return ret / 2 > d;
}

int main()
{
	scanf("%d%lld", &n, &d);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", x + i, y + i);
		a[i].val = x[i], b[i].val = y[i], a[i].id = b[i].id = i;
	}
	sort(a + 1, a + n + 1, cmp);
	sort(b + 1, b + n + 1, cmp);
	for (int i = 1; i <= n; i++) ranka[a[i].id] = i;
	for (int i = 1; i <= n; i++) rankb[b[i].id] = i;
	l = 2, r = n;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check()) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
