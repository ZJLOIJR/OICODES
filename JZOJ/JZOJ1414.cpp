#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e2 + 7, INF = 2147483647;

int n, ans = 0;
struct pane { int h, l, r; } a[N];
int cmp(pane x, pane y) { return x.h < y.h; }

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].h, &a[i].l, &a[i].r);
	a[++n].h = 0, a[n].l = 1, a[n].r = 10000;
	sort(a + 1, a + n + 1, cmp);
	for (int i = 2; i <= n; i++)
	{
		int minlen = INF;
		for (int j = 1; j <= i - 1; j++)
			if (a[j].l <= a[i].r - 0.5 && a[i].r - 0.5 <= a[j].r && a[i].h - a[j].h < minlen) minlen = a[i].h - a[j].h;
		ans += minlen;
		minlen = INF;
		for (int j = 1; j <= i - 1; j++)
			if (a[j].l <= a[i].l + 0.5 && a[i].l + 0.5 <= a[j].r && a[i].h - a[j].h < minlen) minlen = a[i].h - a[j].h;
		ans += minlen;
	}
	printf("%d\n", ans);
	return 0;
}
