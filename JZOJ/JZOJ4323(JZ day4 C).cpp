#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 45;

int n;
int a[N][N], col[N * N], lin[N * N];

int main()
{
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);

	memset(a, 0, sizeof(a));
	scanf("%d", &n);
	a[1][(n + 1) / 2] = 1, col[1] = (n + 1) / 2, lin[1] = 1;
	for (int i = 2; i <= n * n; i++)
	{
		if (lin[i - 1] == 1 && col[i - 1] != n)
			col[i] = col[i - 1] + 1, lin[i] = n, a[lin[i]][col[i]] = i;
		else if (col[i - 1] == n && lin[i - 1] != 1)
			col[i] = 1, lin[i] = lin[i - 1] - 1, a[lin[i]][col[i]] = i;
		else if (lin[i - 1] == 1 && col[i - 1] == n)
			col[i] = col[i - 1], lin[i] = lin[i - 1] + 1, a[lin[i]][col[i]] = i;
		else if (lin[i - 1] != 1 && col[i - 1] != n)
		{
			if (!a[lin[i - 1] - 1][col[i - 1] + 1])
				lin[i] = lin[i - 1] - 1, col[i] = col[i - 1] + 1, a[lin[i]][col[i]] = i;
			else
				col[i] = col[i - 1], lin[i] = lin[i - 1] + 1, a[lin[i]][col[i]] = i;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++) printf("%d ", a[i][j]);
		printf("\n");
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}