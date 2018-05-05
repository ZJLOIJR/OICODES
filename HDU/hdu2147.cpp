#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2e3 + 3;

int n, m;
short sg[N][N];

int main()
{
	for (int i = 1; i <= N - 3; i++)
		for (int j = 1; j <= N - 3; j++)
		{
			if (i == 1 && j == 1) continue;
			if (i - 1 > 0 && !sg[i - 1][j]) sg[i][j] = 1;
			if (j - 1 > 0 && !sg[i][j - 1]) sg[i][j] = 1;
			if (i - 1 > 0 && j - 1 > 0 && !sg[i - 1][j - 1]) sg[i][j] = 1;
		}
	scanf("%d%d", &n, &m);
	while (n || m)
	{
		printf(sg[n][m] ? "Wonderful!\n" : "What a pity!\n");
		scanf("%d%d", &n, &m);
	}
	return 0;
}
