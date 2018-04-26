#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e4 + 3;

int n, x, y, ans = -1;
int a[N], b[N], g[N], k[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d%d", a + i, b + i, g + i, k + i);
	scanf("%d%d", &x, &y);
	for (int i = 1; i <= n; i++) if (x >= a[i] && x <= a[i] + g[i] - 1 && y >= b[i] && y <= b[i] + k[i] - 1) ans = i;
	printf("%d\n", ans);
	return 0;
}
