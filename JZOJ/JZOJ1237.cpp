#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2e3 + 3;

int n, m, ans;
int f[N][N];
char map[N][N];

inline int max(int a, int b) { return a > b ? a : b; }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &map[i][j]);
	ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] == 'X') continue;
			if (map[i - 1][j] == '.') f[i][j] = max(f[i][j], f[i - 1][j] + 2);
			if (map[i][j - 1] == '.') f[i][j] = max(f[i][j], f[i][j - 1] + 2);
		}
	printf("%d\n", ans);
	return 0;
}
