#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 6e5 + 7;

int n, l, r, mid, ans = -1;
struct note { int val, id; } a[N], b[N];
ll d, bucx[N], bucy[N];

int cmp(note p, note q) { return p.val < q.val; }

int check()
{
	memset(bucx, -1, sizeof(bucx));
	memset(bucy, -1, sizeof(bucy));
	ll ret = 0, s = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i].id <= mid) bucx[i] = a[i].val;
		if (b[i].id <= mid) bucy[i] = b[i].val;
	}
	for (register int i = 1, cnt = 0; i <= n; i++)
		if (bucx[i] > -1)
			cnt++, s += bucx[i], ret += cnt * bucx[i] - s;
	s = 0;
	for (register int i = 1, cnt = 0; i <= n; i++)
		if (bucy[i] > -1)
			cnt++, s += bucy[i], ret += cnt * bucy[i] - s;
	return ret > d;
}

int main()
{
	scanf("%d%lld", &n, &d);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i].val, &b[i].val);
		a[i].id = b[i].id = i;
	}
	sort(a + 1, a + n + 1, cmp);
	sort(b + 1, b + n + 1, cmp);
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
