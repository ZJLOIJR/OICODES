#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 137;
typedef long long ll;

int d, n, x, y, xx, yy;
ll a[N][N], sum[N][N], k, mxans = 0, mxcnt;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline ll min(ll a, ll b) { return a < b ? a : b; }
inline ll max(ll a, ll b) { return a > b ? a : b; }

int main()
{
	d = read(), n = read();
	for (int i = 1; i <= n; i++)
		x = read(), y = read(), k = read(),
		a[x + 1][y + 1] = k;
	for (int i = 1; i <= 129; i++)
		for (int j = 1; j <= 129; j++)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	for (int i = 1; i <= 129; i++)
		for (int j = 1; j <= 129; j++)
			x = max(i - d, 1), y = max(j - d, 1),
			xx = min(i + d, 129), yy = min(j + d, 129),
			mxans = max(mxans, sum[xx][yy] - sum[x - 1][yy] - sum[xx][y - 1] + sum[x - 1][y - 1]);
	for (int i = 1; i <= 129; i++)
		for (int j = 1; j <= 129; j++)
		{
			x = max(i - d, 1), y = max(j - d, 1);
			xx = min(i + d, 129), yy = min(j + d, 129);
			if (sum[xx][yy] - sum[x - 1][yy] - sum[xx][y - 1] + sum[x - 1][y - 1] == mxans) mxcnt++;
		}
	printf("%lld %lld\n", mxcnt, mxans);
	return 0;
}
