#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2e3 + 3;

int n, m, ans;
char map[N][N];
int f[N][N];

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf(" %c", &map[i][j]);
			if (map[i][j] == '.')
			{
				f[i][j] = 1;
				if (map[i][j - 1] == '.') f[i][j] += f[i][j - 1];
			}
		}
	ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (map[i][j] == '.')
			{
				int minn = 2147483647;
				for (int k = i; k >= 1 && map[k][j] == '.'; k--)
				{
					minn = min(minn, f[k][j]);
					ans = max(ans, ((i - k + 1) + minn) * 2);
				}
			}
	printf("%d\n", ans - 1);
	return 0;
}
