#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 100, M = 10;

int n, m, full, f[2][1 << M][1 << M];
char map[N + 3][M + 3];

inline int bit(int x) { return (1 << (x - 1)); }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &map[i][j]);
	full = (1 << m) - 1;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= full; j++)
			for (int k = 0; k <= full; k++)
			{
				for (int l = 0; l <= full; l++)
				{
					if ((j | k) & l) continue;
					int flag = 0;
					for (int i = 1; i <= 
				}
			}
	}
	return 0;
}
