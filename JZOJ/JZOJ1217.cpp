#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 3;

int n, m, l, r, mid, ans;
int d1[N], d2[N], f[N][N];

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

int check()
{
	memset(f, 128, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++)
			for (int k = 0; k <= min(j, mid / d1[i]); k++)
				f[i][j] = max(f[i][j], f[i - 1][j - k] + (mid - d1[i] * k) / d2[i]);
	return f[n][m] >= m;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", d1 + i, d2 + i);
	l = 0, r = 1e5;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check()) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
