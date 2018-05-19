#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
inline int max(int a, int b) { return a > b ? a : b; }

const int N = 1e2 + 7, M = 1e5 + 7;

int n, m, l, r, mid, ans;
int x[N], y[N], w, v, f[N][M];

int check()
{
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (sum > m) return 0;
		if (x[i] * mid < y[i]) continue;
		sum += lower_bound(f[i] + 1, f[i] + m + 1, x[i] * mid - y[i]) - f[i];
	}
	return sum <= m;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d%d", x + i, y + i, &w, &v);
		for (int j = v; j <= m; j++) f[i][j] = max(f[i][j], f[i][j - v] + w);
		scanf("%d%d", &w, &v);
		for (int j = v; j <= m; j++) f[i][j] = max(f[i][j], f[i][j - v] + w);
	}
	l = 0, r = m;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check()) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}
