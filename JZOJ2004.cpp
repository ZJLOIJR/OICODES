#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1007;
typedef long long ll;

int n, m, c, x, y;
ll maxans = 0, tmp;
ll sum[N][N];

inline ll max(ll a, ll b) { return a > b ? a : b; }

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int main()
{
	n = read(), m = read(), c = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			tmp = read(),
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + tmp;
	for (int i = 1; i <= n - c + 1; i++)
		for (int j = 1; j <= m - c + 1; j++)
			if (sum[i + c - 1][j + c - 1] - sum[i - 1][j + c - 1] - sum[i + c - 1][j - 1] + sum[i - 1][j - 1] > maxans)
				maxans = sum[i + c - 1][j + c - 1] - sum[i - 1][j + c - 1] - sum[i + c - 1][j - 1] + sum[i - 1][j - 1],
				x = i, y = j;
	printf("%d %d\n", x, y);
	return 0;
}
