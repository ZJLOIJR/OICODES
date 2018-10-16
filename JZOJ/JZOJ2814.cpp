#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 4e2 + 7;

int ans;
int n, k, a[N][N], sum[N][N];

int getsum(int x1, int y1, int x2, int y2) { return sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1]; }

int check(int w, int h)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i + w - 1 <= n && j + h - 1 <= n && getsum(i, j, i + w - 1, j + h - 1) >= k) return 1;
	return 0;
}

int main()
{
	scanf("%d%d", &n, &k);
	ans = n * n;
	for (int i = 1, x, y; i <= n; i++) scanf("%d%d", &x, &y), a[x][y]++;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	for (int w = 1; w <= n; w++)
	{
		int l = 1, r = n, mid, ret = -1;
		while (l <= r)
		{
			mid = l + r >> 1;
			if (check(w, mid)) r = mid - 1, ret = mid;
			else l = mid + 1;
		}
		ans = min(ans, w * ret);
	}
	printf("%d\n", ans);
	return 0;
}
