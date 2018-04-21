#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))
using namespace std;

const int N = 1e3 + 3;

int n, m, ans = 0;
int map[N][N], cnt[N];

int main()
{
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);
	for (int i = 1; i <= n; i++)
	{
		int tot = 0;
		for (int j = 1; j <= m; j++) if (map[i][j] < 0) tot++;
		if (tot >= m / 2) ans++;
		else
			for (int j = 1; j <= m; j++)
			if (map[i][j] < 0)
			{
				if (cnt[j]) { printf("impossible\n"); return 0; }
				cnt[j]++, ans++;
				for (int k = 1; k <= n; k++) map[k][j] = -map[k][j];
			}
	}
	printf("%d\n", min(n + m - ans, ans));

	fclose(stdin);
	fclose(stdout);
	return 0;
}
