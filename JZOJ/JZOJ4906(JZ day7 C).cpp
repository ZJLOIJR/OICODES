#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2007;

int t, k, n, m;
long long f[N][N], sum[N][N];

int main()
{
	freopen("problem.in", "r", stdin);
	freopen("problem.out", "w", stdout);

	scanf("%d%d", &t, &k);
	f[0][0] = 1;
	for (int i = 1; i <= 2000; i++)
	{
		f[i][0] = 1;
		for (int j = 1; j <= i; j++)
		{
			f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % k;
			if (f[i][j] == 0) sum[i][j]++;
		}
	}
	for (int i = 1; i <= 2000; i++)
		for (int j = 1; j <= i; j++)
			if (i == j) sum[i][j] += sum[i][j - 1];
			else sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
	while (t--)
	{
		scanf("%d%d", &n, &m);
		if (m > n) m = n;
		printf("%lld\n", sum[n][m]);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}