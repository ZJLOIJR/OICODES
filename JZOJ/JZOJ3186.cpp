#include <cstdio>
#include <cstring>
#include <cstdlib>

int n, q, l, r, mid, ans, R, G, B;
int sum[257][257][257];

inline int read();
void init();
inline int qrysum(int x1, int y1, int z1, int x2, int y2, int z2);
int check(int m);
void solve();

int main()
{
	init();
	solve();
	return 0;
}

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

void init()
{
	n = read(), q = read();
	while (n--)
	{
		R = read(), G = read(), B = read();
		sum[R + 1][G + 1][B + 1]++;
	}
	for (int i = 1; i <= 256; i++)
		for (int j = 1; j <= 256; j++)
			for (int k = 1; k <= 256; k++)
				sum[i][j][k] += sum[i - 1][j][k] + sum[i][j - 1][k] + sum[i][j][k - 1] + sum[i - 1][j - 1][k - 1] - sum[i - 1][j - 1][k] - sum[i - 1][j][k - 1] - sum[i][j - 1][k - 1];
}

inline int qrysum(int x1, int y1, int z1, int x2, int y2, int z2)
{
	return sum[x2][y2][z2] - sum[x1 - 1][y2][z2] - sum[x2][y1 - 1][z2] - sum[x2][y2][z1 - 1] - sum[x1 - 1][y1 - 1][z1 - 1] + sum[x1 - 1][y1 - 1][z2] + sum[x1 - 1][y2][z1 - 1] + sum[x2][y1 - 1][z1 - 1];
}

int check(int m)
{
	for (int i = m + 1; i <= 256; i++)
		for (int j = m + 1; j <= 256; j++)
			for (int k = m + 1; k <= 256; k++)
				if (qrysum(i - m, j - m, k - m, i, j, k) >= q)
					return 1;
	return 0;
}

void solve()
{
	l = 0, r = 255;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (check(mid))
			r = mid - 1, ans = mid;
		else
			l = mid + 1;
	}
	printf("%d\n", ans);
}
