#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int R = 100, C = 100;
int r, c, ans = 0;
int a[R + 5][C + 5], f[R + 5][C + 5];

int getDP(int i, int j)
{
	if (f[i][j] > 1) return f[i][j];
	int maxx = 1;
	if (a[i + 1][j] < a[i][j] & i + 1 <= r)
	{
		int dp = getDP(i + 1, j) + 1;
		maxx = max(maxx, dp);
	}
	if (a[i][j + 1] < a[i][j] & j + 1 <= c)
	{
		int dp = getDP(i, j + 1) + 1;
		maxx = max(maxx, dp);
	}
	if (a[i - 1][j] < a[i][j] & i - 1 > 0)
	{
		int dp = getDP(i - 1, j) + 1;
		maxx = max(maxx, dp);
	}
	if (a[i][j - 1] < a[i][j] & j - 1 > 0)
	{
		int dp = getDP(i, j - 1) + 1;
		maxx = max(maxx, dp);
	}
	return maxx;
}

int main()
{
	scanf("%d%d", &r, &c);
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
		{
			scanf("%d", &a[i][j]);
			f[i][j] = 1;
		}
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
		{
			f[i][j] = getDP(i, j);
			ans = max(ans, f[i][j]);
		}
	printf("%d\n", ans);
	return 0;
}
