#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int min(int a, int b) { return a < b ? a : b; }

const int N = 1e3 + 7, INF = 0x3f3f3f3f;

int n, ans = INF, w[N], f[N][N];

int dfs(int x, int y)
{
	if (x < 1 || x > n) return INF;
	if (~f[x][y]) return f[x][y];
	int ret = INF;
	ret = min(ret, dfs(x - y, y - 1));
	ret = min(ret, dfs(x + y, y));
	return f[x][y] = ret + w[x];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	memset(f, -1, sizeof(f)), f[1][0] = 0;
	for (int i = 2; i <= n; i++) f[i][0] = INF;
	for (int i = 1; i <= n; i++) ans = min(ans, dfs(n, i));
	printf("%d\n", ans);
	return 0;
}
