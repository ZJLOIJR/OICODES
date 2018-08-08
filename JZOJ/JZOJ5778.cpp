#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int min(int a, int b) { return a < b ? a : b; }
const int N = 5e3 + 7;

int n, m, k, a[N], sum[N][N], f[N][N];

int main()
{
	freopen("vode.in", "r", stdin);
	freopen("vode.out", "w", stdout);
	
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), f[i][m] = 0;
	for (int j = m - 1; j; j--)
		for (int i = 1; i <= n; i++)
		{
			int s = sum[i % n + 1][j + 1] - sum[i % n + 1][min(m, j + k) + 1];
			if (a[i] == a[i % n + 1]) f[i][j] = s ? 1 : 0;
			else f[i][j] = s ? 0 : 1;
			sum[i][j] = sum[i][j + 1] + f[i][j];
		}
	for (int i = 1; i <= n; i++)
	{
		if (sum[i][1] - sum[i][k + 1] > 0) printf("%d ", a[i]);
		else printf("%d ", !a[i]);
	}
	putchar('\n');

	fclose(stdin);
	fclose(stdout);
	return 0;
}
