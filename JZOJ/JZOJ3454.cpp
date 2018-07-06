#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 5e2 + 7;
const double eps = 1e-11;

inline double max(double a, double b) { return a > b ? a : b; }

int n, n1, n2;
double l, r, mid, ans, f[N][N], g[N][N];
struct note { int q1, c1, q2, c2; } a[N];

int cmp(note x, note y) { return (x.q1 - x.c1 * mid) - (x.q2 - x.c2 * mid) > (y.q1 - y.c1 * mid) - (y.q2 - y.c2 * mid); }
int check()
{
	memset(f, -0x3f, sizeof(f));
	memset(g, -0x3f, sizeof(g));
	f[0][0] = g[0][0] = 0;
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = f[i - 1][0];
		for (int j = 1; j <= i; j++) f[i][j] = max(f[i - 1][j], f[i - 1][j - 1] + (a[i].q1 - a[i].c1 * mid));
	}
	for (int i = 1; i <= n; i++)
	{
		g[i][0] = g[i - 1][0];
		for (int j = 1; j <= i; j++) g[i][j] = max(g[i - 1][j], g[i - 1][j - 1] + (a[n - i + 1].q2 - a[n - i + 1].c2 * mid));
	}
	for (int i = 1; i <= n; i++) if (f[i][n1] + g[n - i][n2] >= 0) return 1;
	return 0;
}

int main()
{
	freopen("love.in", "r", stdin);
	freopen("love.out", "w", stdout);

	scanf("%d%d%d", &n, &n1, &n2);
	for (int i = 1; i <= n; i++) scanf("%d%d%d%d", &a[i].q1, &a[i].c1, &a[i].q2, &a[i].c2);
	l = 0, r = 2333333.0;
	while (r - l > eps)
	{
		mid = (l + r) / 2;
		if (check()) l = mid, ans = mid;
		else r = mid;
	}
	printf("%.6lf\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
