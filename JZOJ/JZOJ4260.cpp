#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int max(int a, int b) { return a > b ? a : b; }

const int N = 1e3 + 7;

int n, m, ans;
int a[N][N], b[N][N], top, sta[N], l[N], r[N];

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] = read();
	n--, m--;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			b[i][j] = (a[i][j] + a[i + 1][j + 1] <= a[i + 1][j] + a[i][j + 1]) ? b[i - 1][j] + 1 : 0;
	for (int i = 1; i <= n; i++)
	{
		b[i][0] = b[i][m + 1] = -1;
		sta[top = 1] = 0;
		for (int j = 1; j <= m; j++)
		{
			while (top && b[i][j] <= b[i][sta[top]]) top--;
			l[j] = sta[top] + 1, sta[++top] = j;
		}
		sta[top = 1] = m + 1;
		for (int j = m; j >= 1; j--)
		{
			while (top && b[i][j] <= b[i][sta[top]]) top--;
			r[j] = sta[top] - 1, sta[++top] = j;
		}
		for (int j = 1; j <= m; j++)
		{
			if (!b[i][j]) continue;
			ans = max(ans, (b[i][j] + 1) * (r[j] - l[j] + 2));
		}
	}
	printf("%d\n", ans);
	return 0;
}
